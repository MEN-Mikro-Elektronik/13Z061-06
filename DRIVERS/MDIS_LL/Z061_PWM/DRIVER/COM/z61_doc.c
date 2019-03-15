/*********************  P r o g r a m  -  M o d u l e ***********************/
/*!
 *        \file  z61_doc.c
 *
 *      \author  rla
 *        $Date: 2008/04/29 19:04:39 $
 *    $Revision: 1.2 $
 *
 *      \brief   User documentation for Z61 module driver
 *
 *     Required: -
 *
 *     \switches -
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

/*! \mainpage
	This is the documentation of the MDIS low-level driver for the
	16Z061_PWM	FPGA module.

	The 16Z061_PWM is a PWM generator implemented in an Chameleon FPGA.
	It supports the following features:

	- 16bit Register access to PERIOD and PULSE register

	\n
	\section Variants Variants
	( no variants )
	\n \section FuncDesc Functional Description

	\n \subsection General General

	No hardware initialization is needed to be done by the driver.

	\n \subsection reading Reading the register

	The application can access the PERIOD and PULSE register by GetStat for
	reading and SetStat for writing data.

	\n \section descriptor_entries Descriptor Entries

	The low-level driver initialization routine decodes the following entries
	("keys") in addition to the general descriptor keys:

	<table border="0">
	<tr><td><b>Descriptor entry</b></td>
		<td><b>Description</b></td>
		<td><b>Values</b></td>
	</tr>

	<tr><td>Z061_INIT_PERIOD</td>
		<td>Initial value for PERIOD register</td>
		<td>0..0xFFFF, default: 0</td>
	</tr>
	<tr><td>Z061_INIT_PULSE</td>
		<td>Initial value for PULSE register</td>
		<td>0..0xFFFF, default: 0</td>
	</tr>
	</table>


	\n \section interrupts Interrupts
	The Z061 PWM module doesn't generate any interrupts, so the driver
	doesn't support interrupt/signal handling.

	\n \section api_functions Supported API Functions

	<table border="0">
	<tr>
		<td><b>API function</b></td>
		<td><b>Functionality</b></td>
		<td><b>Corresponding low level function</b></td></tr>

	<tr><td>M_open()</td><td>Open device</td><td>Z61_Init()</td></tr>

	<tr><td>M_close()     </td><td>Close device             </td>
	<td>Z61_Exit())</td></tr>
	<tr><td>M_read()      </td><td>not supported by driver  </td>
	<td>Z61_Read()</td></tr>
	<tr><td>M_write()     </td><td>not supported by driver  </td>
	<td>Z61_Write()</td></tr>
	<tr><td>M_setstat()   </td><td>Writing register access  </td>
	<td>Z61_SetStat()</td></tr>
	<tr><td>M_getstat()   </td><td>Reading register access  </td>
	<td>Z61_GetStat()</td></tr>
	<tr><td>M_getblock()  </td><td>not supported by driver  </td>
	<td>Z61_BlockRead()</td></tr>
	<tr><td>M_setblock()  </td><td>not supported by driver  </td>
	<td>Z61_BlockWrite()</td></tr>
	<tr><td>M_errstringTs() </td><td>Generate error message </td>
	<td>-</td></tr>
	</table>

	\n \section descriptor_entries Descriptor Entries

	The low-level driver initialization routine decodes the following entries
	("keys") in addition to the general descriptor keys:

	<table border="0">
	<tr><td><b>Descriptor entry</b></td>
		<td><b>Description</b></td>
		<td><b>Values</b></td>
	</tr>

	<tr><td>Z061_PERIOD_INIT</td>
		<td>Initial value for PERIOD register</td>
		<td>0..0xFFFF, default: 0</td>
	</tr>
	<tr><td>Z061_PULSE_INIT</td>
		<td>Initial value for PULSE register</td>
		<td>0..0xFFFF, default: 0</td>
	</tr>
	</table>

	\n \section codes Z61 specific Getstat/Setstat codes
	see \ref getstat_setstat_codes "section about Getstat/Setstat codes"


	\n \section Documents Overview of all Documents

	\subsection z61_simp  Simple example for using the driver
	z61_simp.c (see example section)

	\subsection z61_pwm_min   Minimum descriptor
	z61_min.dsc
	demonstrates the minimum set of options necessary for using the drver.

	\subsection z61_pwm_max   Maximum descriptor
	z61_max.dsc
	shows all possible configuration options for this driver.
*/

/** \example z61_simp.c
Simple example for driver usage
*/

/** \page dummy
  \menimages
*/

