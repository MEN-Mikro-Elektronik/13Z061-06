/***********************  I n c l u d e  -  F i l e  ***********************/
/*!
 *        \file  z61_int.h
 *
 *      \author  rla
 *        $Date: 2009/03/02 15:52:37 $
 *    $Revision: 1.3 $
 *
 *       \brief  Header file for Z61 driver containing
 *               Z61 specific status codes and
 *               Z61 function prototypes
 *
 *    \switches  _ONE_NAMESPACE_PER_DRIVER_
 *               _LL_DRV_
 *
 *
 *---------------------------------------------------------------------------
 * Copyright (c) 2006-2019, MEN Mikro Elektronik GmbH
 ****************************************************************************/

 /*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _Z61_INT_H
#define _Z61_INT_H

#ifdef __cplusplus
      extern "C" {
#endif

#define _NO_LL_HANDLE		/* ll_defs.h: don't define LL_HANDLE struct */

#include <MEN/men_typs.h>   /* system dependent definitions   */
#include <MEN/maccess.h>    /* hw access macros and types     */
#include <MEN/dbg.h>        /* debug functions                */
#include <MEN/oss.h>        /* oss functions                  */
#include <MEN/desc.h>       /* descriptor functions           */
#include <MEN/modcom.h>     /* ID PROM functions              */
#include <MEN/mdis_api.h>   /* MDIS global defs               */
#include <MEN/mdis_com.h>   /* MDIS common defs               */
#include <MEN/mdis_err.h>   /* MDIS error codes               */
#include <MEN/ll_defs.h>    /* low-level driver definitions   */

/*-----------------------------------------+
|  DEFINES                                 |
+-----------------------------------------*/
/* general defines */
#define CH_NUMBER			1			/**< number of device channels */
#define USE_IRQ				FALSE		/**< interrupt required  */
#define ADDRSPACE_COUNT		1			/**< nbr of required address spaces */
#define ADDRSPACE_SIZE		16			/**< size of address space */

/* debug defines */
#define DBG_MYLEVEL			llHdl->dbgLevel   /**< debug level */
#define DBH					llHdl->dbgHdl     /**< debug handle */

/** \name 16Z061_PWM register defines
 *  \anchor reg_defines
 */
/**@{*/
#define Z061_PERIOD_ADDR_OFFSET		0x00
		/**< PERIOD register address offset in PWM device */
#define Z061_PULSE_ADDR_OFFSET		0x04
		/**< PULSE register address offset in PWM device */
#define Z061_CHANNEL_OFFSET			0x10
		/**< channel offset */
/**@}*/

/*-----------------------------------------+
|  TYPEDEFS                                |
+-----------------------------------------*/
/** low-level handle */
typedef struct {
	/* general */
    int32           memAlloc;		/**< Size allocated for the handle */
    OSS_HANDLE      *osHdl;         /**< OSS handle */
    OSS_IRQ_HANDLE  *irqHdl;        /**< IRQ handle */
    DESC_HANDLE     *descHdl;       /**< DESC handle */
    MACCESS         ma;             /**< HW access handle */
	MDIS_IDENT_FUNCT_TBL idFuncTbl;	/**< ID function table */
	/* debug */
    u_int32         dbgLevel;		/**< Debug level */
	DBG_HANDLE      *dbgHdl;        /**< Debug handle */
	/* misc */
    u_int32         irqCount;       /**< Interrupt counter */
} LL_HANDLE;

/* include files which need LL_HANDLE */
#include <MEN/ll_entry.h>   /* low-level driver jump table  */
#include <MEN/z61_drv.h>   /* Z61 driver header file */

/*-----------------------------------------+
|  PROTOTYPES                              |
+-----------------------------------------*/
static int32 Z61_Init(DESC_SPEC *descSpec, OSS_HANDLE *osHdl,
					   MACCESS *ma, OSS_SEM_HANDLE *devSemHdl,
					   OSS_IRQ_HANDLE *irqHdl, LL_HANDLE **llHdlP);
static int32 Z61_Exit(LL_HANDLE **llHdlP );
static int32 Z61_Read(LL_HANDLE *llHdl, int32 ch, int32 *value);
static int32 Z61_Write(LL_HANDLE *llHdl, int32 ch, int32 value);
static int32 Z61_SetStat(LL_HANDLE *llHdl,int32 code, int32 ch, INT32_OR_64 value);
static int32 Z61_GetStat(LL_HANDLE *llHdl, int32 code, int32 ch, INT32_OR_64 *valueP);
static int32 Z61_BlockRead(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size,
							int32 *nbrRdBytesP);
static int32 Z61_BlockWrite(LL_HANDLE *llHdl, int32 ch, void *buf, int32 size,
							 int32 *nbrWrBytesP);
static int32 Z61_Irq(LL_HANDLE *llHdl );
static int32 Z61_Info(int32 infoType, ... );

static char* Ident( void );
static int32 Cleanup(LL_HANDLE *llHdl, int32 retCode);

#ifdef __cplusplus
      }
#endif

#endif /* _Z61_INT_H */
