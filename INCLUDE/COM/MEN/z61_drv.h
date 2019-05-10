/***********************  I n c l u d e  -  F i l e  ***********************/
/*!
 *        \file  z61_drv.h
 *
 *      \author  rla
 *        $Date: 2009/07/10 14:13:47 $
 *    $Revision: 3.2 $
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

#ifndef _Z61_DRV_H
#define _Z61_DRV_H

#ifdef __cplusplus
      extern "C" {
#endif


/*-----------------------------------------+
|  TYPEDEFS                                |
+-----------------------------------------*/
/* none */

/*-----------------------------------------+
|  DEFINES                                 |
+-----------------------------------------*/
/** \name Z61 specific Getstat/Setstat standard codes
 *  \anchor getstat_setstat_codes
 */
/**@{*/
#define Z061_PERIOD            M_DEV_OF+0x00   /**< G,S: Access PERIOD
												*   register of PWM device */
#define Z061_PULSE             M_DEV_OF+0x01   /**< G,S: Access PULSE
												*   register of PWM device */
/**@}*/

/*-----------------------------------------+
|  PROTOTYPES                              |
+-----------------------------------------*/
#ifdef _LL_DRV_
#	ifdef _ONE_NAMESPACE_PER_DRIVER_
#		define Z61_GetEntry LL_GetEntry
#	else
#		ifdef Z61_SW
#			define Z61_GetEntry Z61_SW_GetEntry
#		endif /* Z61_SW */
		extern void Z61_GetEntry(LL_ENTRY* drvP);
#	endif
#endif /* _LL_DRV_ */

/*-----------------------------------------+
|  BACKWARD COMPATIBILITY TO MDIS4         |
+-----------------------------------------*/
#ifndef U_INT32_OR_64
 /* we have an MDIS4 men_types.h and mdis_api.h included */
 /* only 32bit compatibility needed!                     */
 #define INT32_OR_64  int32
 #define U_INT32_OR_64 u_int32
 typedef INT32_OR_64  MDIS_PATH;
#endif /* U_INT32_OR_64 */

#ifdef __cplusplus
      }
#endif

#endif /* _Z61_DRV_H */
