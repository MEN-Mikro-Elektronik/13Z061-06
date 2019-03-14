/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  z61_drv.c
 *
 *      \author  rla
 *        $Date: 2009/07/10 14:12:03 $
 *    $Revision: 1.3 $
 *
 *      \brief   Low-level driver for Z61 module
 *
 *     Required: OSS, DESC, DBG, ID libraries
 *
 *     \switches _ONE_NAMESPACE_PER_DRIVER_
 */
 *
 *---------------------------------------------------------------------------
 * Copyright (c) 2006-2019, MEN Mikro Elektronik GmbH
 ****************************************************************************/

#include "z61_int.h"

/****************************** Z61_GetEntry ********************************/
/** Initialize driver's jump table
 *
 *  \param drvP     \OUT Pointer to the initialized jump table structure
 */
#ifdef _ONE_NAMESPACE_PER_DRIVER_
    extern void LL_GetEntry( LL_ENTRY* drvP )
#else
    extern void Z61_GetEntry( LL_ENTRY* drvP )
#endif /* _ONE_NAMESPACE_PER_DRIVER_ */
{
    drvP->init        = Z61_Init;
    drvP->exit        = Z61_Exit;
    drvP->read        = Z61_Read;
    drvP->write       = Z61_Write;
    drvP->blockRead   = Z61_BlockRead;
    drvP->blockWrite  = Z61_BlockWrite;
    drvP->setStat     = Z61_SetStat;
    drvP->getStat     = Z61_GetStat;
    drvP->irq         = Z61_Irq;
    drvP->info        = Z61_Info;
}

/******************************** Z61_Init **********************************/
/** Allocate and return low-level handle, initialize hardware
 *
 * The function initializes all channels with the definitions made
 * in the descriptor. The interrupt is disabled.
 *
 * The function decodes \ref descriptor_entries "these descriptor entries"
 * in addition to the general descriptor keys.
 *
 *  \param descP      \IN  Pointer to descriptor data
 *  \param osHdl      \IN  OSS handle
 *  \param ma         \IN  HW access handle
 *  \param devSemHdl  \IN  Device semaphore handle
 *  \param irqHdl     \IN  IRQ handle
 *  \param llHdlP     \OUT Pointer to low-level driver handle
 *
 *  \return           \c 0 On success or error code
 */
static int32 Z61_Init(
    DESC_SPEC       *descP,
    OSS_HANDLE      *osHdl,
    MACCESS         *ma,
    OSS_SEM_HANDLE  *devSemHdl,
    OSS_IRQ_HANDLE  *irqHdl,
    LL_HANDLE       **llHdlP
)
{
    LL_HANDLE *llHdl = NULL;
    u_int32 gotsize;
    int32 error = 0;
    u_int32 value = 0;

    /*------------------------------+
    |  prepare the handle           |
    +------------------------------*/
	*llHdlP = NULL;		/* set low-level driver handle to NULL */

	/* alloc */
    if ((llHdl = (LL_HANDLE*)OSS_MemGet(
    				osHdl, sizeof(LL_HANDLE), &gotsize)) == NULL)
       return(ERR_OSS_MEM_ALLOC);

	/* clear */
    OSS_MemFill(osHdl, gotsize, (char*)llHdl, 0x00);

	/* init */
    llHdl->memAlloc   = gotsize;
    llHdl->osHdl      = osHdl;
    llHdl->irqHdl     = irqHdl;
    llHdl->ma		  = *ma;

    /*------------------------------+
    |  init id function table       |
    +------------------------------*/
	/* driver's ident function */
	llHdl->idFuncTbl.idCall[0].identCall = Ident;
	/* library's ident functions */
	llHdl->idFuncTbl.idCall[1].identCall = DESC_Ident;
	llHdl->idFuncTbl.idCall[2].identCall = OSS_Ident;
	/* terminator */
	llHdl->idFuncTbl.idCall[3].identCall = NULL;

    /*------------------------------+
    |  prepare debugging            |
    +------------------------------*/
	DBG_MYLEVEL = OSS_DBG_DEFAULT;	/* set OS specific debug level */
	DBGINIT((NULL,&DBH));

    /*------------------------------+
    |  scan descriptor              |
    +------------------------------*/
	/* prepare access */
    if ((error = DESC_Init(descP, osHdl, &llHdl->descHdl)))
		return( Cleanup(llHdl,error) );

    /* DEBUG_LEVEL_DESC */
    if ((error = DESC_GetUInt32(llHdl->descHdl, OSS_DBG_DEFAULT,
								&value, "DEBUG_LEVEL_DESC")) &&
		error != ERR_DESC_KEY_NOTFOUND)
		return( Cleanup(llHdl,error) );

	DESC_DbgLevelSet(llHdl->descHdl, value);	/* set level */

    /* DEBUG_LEVEL */
    if ((error = DESC_GetUInt32(llHdl->descHdl, OSS_DBG_DEFAULT,
								&llHdl->dbgLevel, "DEBUG_LEVEL")) &&
		error != ERR_DESC_KEY_NOTFOUND)
		return( Cleanup(llHdl,error) );

    DBGWRT_1((DBH, "LL - Z61_Init\n"));

    /*------------------------------+
    |  init hardware                |
    +------------------------------*/
	value = 0;

	if ((error = DESC_GetUInt32(llHdl->descHdl, 0,
							&value, "Z061_PERIOD_INIT")) &&
		error != ERR_DESC_KEY_NOTFOUND)
		return( Cleanup(llHdl,error) );

	if( value > 0xFFFF ){
		value = 0xFFFF;
	}

	/* write initial value to PWM PERIOD register */
	MWRITE_D32(llHdl->ma, Z061_PERIOD_ADDR_OFFSET, (u_int16)value);

	value = 0;

	if ((error = DESC_GetUInt32(llHdl->descHdl, 0,
							&value, "Z061_PULSE_INIT")) &&
	error != ERR_DESC_KEY_NOTFOUND)
	return( Cleanup(llHdl,error) );

	if( value > 0xFFFF ){
		value = 0xFFFF;
	}

	/* write initial value to PWM PULSE register */
	MWRITE_D32(llHdl->ma, Z061_PULSE_ADDR_OFFSET, (u_int16)value);

	*llHdlP = llHdl;	/* set low-level driver handle */

	return(ERR_SUCCESS);
}

/****************************** Z61_Exit ************************************/
/** De-initialize hardware and clean up memory
 *
 *  The function deinitializes all channels by setting them to ???.
 *  The interrupt is disabled.
 *
 *  \param llHdlP      \IN  Pointer to low-level driver handle
 *
 *  \return           \c 0 On success or error code
 */
static int32 Z61_Exit(
   LL_HANDLE    **llHdlP
)
{
    LL_HANDLE *llHdl = *llHdlP;
	int32 error = 0;

    DBGWRT_1((DBH, "LL - Z61_Exit\n"));

    /*------------------------------+
    |  de-init hardware             |
    +------------------------------*/
	/* ... */

    /*------------------------------+
    |  clean up memory               |
    +------------------------------*/
	*llHdlP = NULL;		/* set low-level driver handle to NULL */
	error = Cleanup(llHdl,error);

	return(error);
}

/****************************** Z61_Read ************************************/
/** Read a value from the device, not supported by this driver
 *
 *  \return           \c ERR_LL_ILL_FUNC
 */
static int32 Z61_Read(
    LL_HANDLE *llHdl,
    int32 ch,
    int32 *valueP
)
{
	return(ERR_LL_ILL_FUNC);
}

/****************************** Z61_Write ***********************************/
/** Write a value to the device, not supported by this driver
 *
 *  \return           \c ERR_LL_ILL_FUNC
 */
static int32 Z61_Write(
    LL_HANDLE *llHdl,
    int32 ch,
    int32 value
)
{
	return(ERR_LL_ILL_FUNC);
}

/****************************** Z61_SetStat *********************************/
/** Set the driver status
 *
 *  The driver supports \ref getstat_setstat_codes "these status codes"
 *  in addition to the standard codes (see mdis_api.h).
 *
 *  \param llHdl  	  \IN  Low-level handle
 *  \param code       \IN  \ref getstat_setstat_codes "status code"
 *  \param ch         \IN  Current channel
 *  \param value32_or_64      \IN  Data or
 *                         pointer to block data structure (M_SG_BLOCK) for
 *                         block status codes
 *  \return           \c 0 On success or error code
 */
static int32 Z61_SetStat(
    LL_HANDLE *llHdl,
    int32  code,
    int32  ch,
    INT32_OR_64 value32_or_64
)
{
	int32 value	= (int32)value32_or_64;	/* 32bit value     */

	int32 error = ERR_SUCCESS;

    DBGWRT_1((DBH, "LL - Z61_SetStat: ch=%d code=0x%04x value=0x%x\n",
			  ch,code,value));

    switch(code) {
        /*--------------------------+
        |  debug level              |
        +--------------------------*/
        case M_LL_DEBUG_LEVEL:
            llHdl->dbgLevel = value;
            break;
        /*--------------------------+
        |  enable interrupts        |
        +--------------------------*/
        case M_MK_IRQ_ENABLE:
			error = ERR_LL_UNK_CODE;	/* say: not supported */
            break;
        /*--------------------------+
        |  set irq counter          |
        +--------------------------*/
        case M_LL_IRQ_COUNT:
            llHdl->irqCount = value;
            break;
        /*--------------------------+
        |  set PERIOD register      |
        +--------------------------*/
        case Z061_PERIOD:
			MWRITE_D32(llHdl->ma, Z061_PERIOD_ADDR_OFFSET, value);
			break;
        /*--------------------------+
        |  set PULSE register       |
        +--------------------------*/
        case Z061_PULSE:
			MWRITE_D32(llHdl->ma, Z061_PULSE_ADDR_OFFSET, value);
			break;
        /*--------------------------+
        |  (unknown)                |
        +--------------------------*/
        default:
            error = ERR_LL_UNK_CODE;
    }

	return(error);
}

/****************************** Z61_GetStat *********************************/
/** Get the driver status
 *
 *  The driver supports \ref getstat_setstat_codes "these status codes"
 *  in addition to the standard codes (see mdis_api.h).
 *
 *  \param llHdl      \IN  Low-level handle
 *  \param code       \IN  \ref getstat_setstat_codes "status code"
 *  \param ch         \IN  Current channel
 *  \param value32_or_64P     \IN  Pointer to block data structure (M_SG_BLOCK) for
 *                         block status codes
 *  \param value32_or_64P     \OUT Data pointer or pointer to block data structure
 *                         (M_SG_BLOCK) for block status codes
 *
 *  \return           \c 0 On success or error code
 */
static int32 Z61_GetStat(
    LL_HANDLE *llHdl,
    int32  code,
    int32  ch,
    INT32_OR_64  *value32_or_64P
)
{
	int32		*valueP	  = (int32*)value32_or_64P;		 /* pointer to 32bit value  */
	INT32_OR_64	*value64P = value32_or_64P;		 		 /* stores 32/64bit pointer  */

	int32 error = ERR_SUCCESS;

    DBGWRT_1((DBH, "LL - Z61_GetStat: ch=%d code=0x%04x\n",
			  ch,code));

    switch(code)
    {
        /*--------------------------+
        |  debug level              |
        +--------------------------*/
        case M_LL_DEBUG_LEVEL:
            *valueP = llHdl->dbgLevel;
            break;
        /*--------------------------+
        |  number of channels       |
        +--------------------------*/
        case M_LL_CH_NUMBER:
            *valueP = CH_NUMBER;
            break;
        /*--------------------------+
        |  irq counter              |
        +--------------------------*/
        case M_LL_IRQ_COUNT:
            *valueP = llHdl->irqCount;
            break;
        /*--------------------------+
        |   ident table pointer     |
        |   (treat as non-block!)   |
        +--------------------------*/
        case M_MK_BLK_REV_ID:
           *value64P = (INT32_OR_64)&llHdl->idFuncTbl;
           break;
        /*--------------------------+
        |  get PERIOD register      |
        +--------------------------*/
        case Z061_PERIOD:
            *valueP = MREAD_D32( llHdl->ma, Z061_PERIOD_ADDR_OFFSET);
		    DBGWRT_1((DBH, "LL - Z61_GetStat: ch=%d code=0x%04x value=0x%x\n",
			  ch,code,*valueP));

            break;
        /*--------------------------+
        |  get PULSE register       |
        +--------------------------*/
        case Z061_PULSE:
            *valueP = MREAD_D32( llHdl->ma, Z061_PULSE_ADDR_OFFSET);
		    DBGWRT_1((DBH, "LL - Z61_GetStat: ch=%d code=0x%04x value=0x%x\n",
			  ch,code,*valueP));

            break;
        /*--------------------------+
        |  unknown                  |
        +--------------------------*/
        default:
            error = ERR_LL_UNK_CODE;
    }

	return(error);
}

/******************************* Z61_BlockRead ******************************/
/** Read a block from the device, not supported by this driver
 *
 *  \return           \c ERR_LL_ILL_FUNC
 */
static int32 Z61_BlockRead(
     LL_HANDLE *llHdl,
     int32     ch,
     void      *buf,
     int32     size,
     int32     *nbrRdBytesP
)
{
	return(ERR_LL_ILL_FUNC);
}

/****************************** Z61_BlockWrite ******************************/
/** Write a block to the device, not supported by this driver
 *
 *  \return           \c ERR_LL_ILL_FUNC
 */
static int32 Z61_BlockWrite(
     LL_HANDLE *llHdl,
     int32     ch,
     void      *buf,
     int32     size,
     int32     *nbrWrBytesP
)
{
	return(ERR_LL_ILL_FUNC);
}


/****************************** Z61_Irq ************************************/
/** Interrupt service routine
 *  No Interrupts are generated by the Z61 Chameleon device
 *
 *  \param llHdl  	   \IN  Low-level handle
 *  \return LL_IRQ_DEVICE	IRQ caused by device
 *          LL_IRQ_DEV_NOT  IRQ not caused by device
 *          LL_IRQ_UNKNOWN  Unknown
 */
static int32 Z61_Irq(
   LL_HANDLE *llHdl
)
{
    IDBGWRT_1((DBH, ">>> Z61_Irq:\n"));

	/* ... */

	llHdl->irqCount++;

	return(LL_IRQ_DEV_NOT);	/* not my interrupt */
}

/****************************** Z61_Info ***********************************/
/** Get information about hardware and driver requirements
 *
 *  The following info codes are supported:
 *
 * \code
 *  Code                      Description
 *  ------------------------  -----------------------------
 *  LL_INFO_HW_CHARACTER      Hardware characteristics
 *  LL_INFO_ADDRSPACE_COUNT   Number of required address spaces
 *  LL_INFO_ADDRSPACE         Address space information
 *  LL_INFO_IRQ               Interrupt required
 *  LL_INFO_LOCKMODE          Process lock mode required
 * \endcode
 *
 *  The LL_INFO_HW_CHARACTER code returns all address and
 *  data modes (ORed) which are supported by the hardware
 *  (MDIS_MAxx, MDIS_MDxx).
 *
 *  The LL_INFO_ADDRSPACE_COUNT code returns the number
 *  of address spaces used by the driver.
 *
 *  The LL_INFO_ADDRSPACE code returns information about one
 *  specific address space (MDIS_MAxx, MDIS_MDxx). The returned
 *  data mode represents the widest hardware access used by
 *  the driver.
 *
 *  The LL_INFO_IRQ code returns whether the driver supports an
 *  interrupt routine (TRUE or FALSE).
 *
 *  The LL_INFO_LOCKMODE code returns which process locking
 *  mode the driver needs (LL_LOCK_xxx).
 *
 *  \param infoType	   \IN  Info code
 *  \param ...         \IN  Argument(s)
 *
 *  \return            \c 0 On success or error code
 */
static int32 Z61_Info(
   int32  infoType,
   ...
)
{
    int32   error = ERR_SUCCESS;
    va_list argptr;

    va_start(argptr, infoType );

    switch(infoType) {
		/*-------------------------------+
        |  hardware characteristics      |
        |  (all addr/data modes ORed)   |
        +-------------------------------*/
        case LL_INFO_HW_CHARACTER:
		{
			u_int32 *addrModeP = va_arg(argptr, u_int32*);
			u_int32 *dataModeP = va_arg(argptr, u_int32*);

			*addrModeP = MDIS_MA08;
			*dataModeP = MDIS_MD08 | MDIS_MD16;
			break;
	    }
		/*-------------------------------+
        |  nr of required address spaces |
        |  (total spaces used)           |
        +-------------------------------*/
        case LL_INFO_ADDRSPACE_COUNT:
		{
			u_int32 *nbrOfAddrSpaceP = va_arg(argptr, u_int32*);

			*nbrOfAddrSpaceP = ADDRSPACE_COUNT;
			break;
	    }
		/*-------------------------------+
        |  address space type            |
        |  (widest used data mode)       |
        +-------------------------------*/
        case LL_INFO_ADDRSPACE:
		{
			u_int32 addrSpaceIndex = va_arg(argptr, u_int32);
			u_int32 *addrModeP = va_arg(argptr, u_int32*);
			u_int32 *dataModeP = va_arg(argptr, u_int32*);
			u_int32 *addrSizeP = va_arg(argptr, u_int32*);

			if (addrSpaceIndex >= ADDRSPACE_COUNT)
				error = ERR_LL_ILL_PARAM;
			else {
				*addrModeP = MDIS_MA08;
				*dataModeP = MDIS_MD16;
				*addrSizeP = ADDRSPACE_SIZE;
			}

			break;
	    }
		/*-------------------------------+
        |   interrupt required           |
        +-------------------------------*/
        case LL_INFO_IRQ:
		{
			u_int32 *useIrqP = va_arg(argptr, u_int32*);

			*useIrqP = USE_IRQ;
			break;
	    }
		/*-------------------------------+
        |   process lock mode            |
        +-------------------------------*/
        case LL_INFO_LOCKMODE:
		{
			u_int32 *lockModeP = va_arg(argptr, u_int32*);

			*lockModeP = LL_LOCK_CALL;
			break;
	    }
		/*-------------------------------+
        |   (unknown)                    |
        +-------------------------------*/
        default:
          error = ERR_LL_ILL_PARAM;
    }

    va_end(argptr);
    return(error);
}

/*******************************  Ident  ***********************************/
/** Return ident string
 *
 *  \return            Pointer to ident string
 */
static char* Ident( void )
{
    return( "Z61 - Z61 low-level driver: "
#ifdef MAC_BYTESWAP
    "swapped "
#else
    "non swapped "
#endif
"$Id: z61_drv.c,v 1.3 2009/07/10 14:12:03 CRuff Exp $" );
}

/********************************* Cleanup *********************************/
/** Close all handles, free memory and return error code
 *
 *	\warning The low-level handle is invalid after this function is called.
 *
 *  \param llHdl      \IN  Low-level handle
 *  \param retCode    \IN  Return value
 *
 *  \return           \IN   retCode
 */
static int32 Cleanup(
   LL_HANDLE    *llHdl,
   int32        retCode
)
{
    /*------------------------------+
    |  close handles                |
    +------------------------------*/
	/* clean up desc */
	if (llHdl->descHdl)
		DESC_Exit(&llHdl->descHdl);

	/* clean up debug */
	DBGEXIT((&DBH));

    /*------------------------------+
    |  free memory                  |
    +------------------------------*/
    /* free my handle */
    OSS_MemFree(llHdl->osHdl, (int8*)llHdl, llHdl->memAlloc);

    /*------------------------------+
    |  return error code            |
    +------------------------------*/
	return(retCode);
}


