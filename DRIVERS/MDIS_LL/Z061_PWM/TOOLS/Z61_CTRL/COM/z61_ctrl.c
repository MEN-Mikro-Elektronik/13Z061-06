/****************************************************************************
 ************                                                    ************
 ************                    Z61_CTRL                        ************
 ************                                                    ************
 ****************************************************************************/
/*!
 *        \file  z61_ctrl.c
 *      \author  dieter.pfeuffer@men.de
 *
 *       \brief  Tool to control the 16Z061-01 PWM generator 
 *
 *               Can also be used for 16Z061-00 but then the generated cycle
 *               and pulse length is one system clock cycle longer than
 *               configured and PWM signal can not be set to permanent low.
 *
 *     Required: libraries: mdis_api, usr_oss, usr_utl
 *    \switches  (none)
 *
 *
 *---------------------------------------------------------------------------
 * Copyright 2016-2019, MEN Mikro Elektronik GmbH
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

/*--------------------------------------+
|  INCLUDES                             |
+--------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <MEN/men_typs.h>
#include <MEN/mdis_api.h>
#include <MEN/usr_oss.h>
#include <MEN/usr_utl.h>
#include <MEN/z61_drv.h>

static const char IdentString[]=MENT_XSTR(MAK_REVISION);

/*--------------------------------------+
|   DEFINES                             |
+--------------------------------------*/
#define ERR_OK			0
#define ERR_PARAM		1
#define ERR_FUNC		2
#define DEF_CLK			33000000

/*--------------------------------------+
|   GLOBALS                             |
+--------------------------------------*/
static MDIS_PATH G_path;
static u_int32	 G_verbose;
static u_int32	 G_verify;
static int32	 G_cycleClkNibble;
static int32	 G_pulseClkNibble;

/*--------------------------------------+
|  PROTOTYPES                           |
+--------------------------------------*/
static void Usage(void);
static int32 PrintError(char *info);
static int32 Time2Clock(int32 sysFreq, int32 timeUs);
static int32 ConfigPwm(int32 sysFreq, int32 cycleClk, int32 pulseClk);
static void PrintPwmSetting(int32 sysFreq, int32 cycleClk, int32 pulseClk);

/********************************* Usage ***********************************/
/**  Print program usage
 */
static void Usage(void)
{
	printf("Usage:    z61_ctrl <device> <opts> [<opts>]                              \n");
	printf("Function: Control the 16Z061-01 PWM generator                               \n");
	printf("Options:                                                     [default]   \n");
	printf("    device      device name (e.g. pwm_1)                                 \n");
	printf("--- specify PWM as time ---                                              \n");
	printf("    -c=<us>     cycle length in time [us]                                \n");
	printf("    -p=<us>     pulse length in time [us]....................[-c=<ms>/2] \n");
	printf("    -f=<Hz>     system clock frequency [Hz]..................[%d]        \n", DEF_CLK);
	printf("--- OR specify PWM as system clock cycles ---                            \n");
	printf("    -C=<n>      cycle length in nbr of system clock cycles               \n");
	printf("                range: 1..65535                                          \n");
	printf("    -P=<n>      pulse length in nbr of system clock cycles...[-C=<n>/2]  \n");
	printf("                range: 0..65535                                          \n");
	printf("--- OR perform endless PWM test ---                                      \n");
	printf("    -t=<n>      PWM test until keypress:                                 \n");
	printf("                1= sweep cycle length from min..max                      \n");
	printf("                   with 50%% pulse length                                \n");
	printf("                2= sweep pulse length from min..max                      \n");
	printf("                   with max cycle length                                 \n");
	printf("    -s=<n>      step width for loop..........................[64]        \n");
	printf("    -d=<ms>     delay [ms] after each cycle/pulse change.....[10]        \n");
	printf("    -a=<n>      abort after n passes                                     \n");
	printf("    -v          verbose output for PWM test                              \n");
	printf("    -V=0,1      verify set cycle and pulse length                        \n");
	printf("                0= abort on error                                        \n");
	printf("                1= continue on error                                     \n");
	printf("\n");
	printf("Copyright 2016-2019, MEN Mikro Elektronik GmbH\n%s\n", IdentString);
}

/***************************************************************************/
/** Program main function
 *
 *  \param argc       \IN  argument counter
 *  \param argv       \IN  argument vector
 *
 *  \return           success (0) or error code
 */
int main(int argc, char *argv[])
{
	char	*device, *str, *errstr, buf[40];
	u_int32	n;
	int32	cycleUs, pulseUs, sysFreq, cycleClk, pulseClk, test, step, delay, abort; 
	int32	loopcnt, run;	
	int32	ret;

	/*----------------------+
	|  check arguments      |
	+----------------------*/
	if ((errstr = UTL_ILLIOPT("c=p=f=C=P=t=s=d=a=vV=?", buf))) {
		printf("*** %s\n", errstr);
		return ERR_PARAM;
	}
	if (UTL_TSTOPT("?")) {
		Usage();
		return ERR_PARAM;
	}
	if (argc < 2) {
		Usage();
		return ERR_PARAM;
	}

	/*----------------------+
	|  get arguments        |
	+----------------------*/
	for (device = NULL, n=1; n<argc; n++) {
		if (*argv[n] != '-') {
			device = argv[n];
			break;
		}
	}
	if (!device) {
		Usage();
		return ERR_PARAM;
	}

	cycleUs   = ((str = UTL_TSTOPT("c=")) ? atoi(str) : -1);
	pulseUs   = ((str = UTL_TSTOPT("p=")) ? atoi(str) : -1);
	sysFreq   = ((str = UTL_TSTOPT("f=")) ? atoi(str) : DEF_CLK);
	cycleClk  = ((str = UTL_TSTOPT("C=")) ? atoi(str) : -1);
	pulseClk  = ((str = UTL_TSTOPT("P=")) ? atoi(str) : -1);
	test      = ((str = UTL_TSTOPT("t=")) ? atoi(str) : -1);
	step      = ((str = UTL_TSTOPT("s=")) ? atoi(str) : 64);
	delay     = ((str = UTL_TSTOPT("d=")) ? atoi(str) : 10);
	abort     = ((str = UTL_TSTOPT("a=")) ? atoi(str) : -1);
	G_verbose = (UTL_TSTOPT("v") ? 1 : 0);
	G_verify = ((str = UTL_TSTOPT("V=")) ? atoi(str) : -1);

	/* further parameter checking */
	if ((cycleUs == -1) && (cycleClk == -1) && (test == -1)) {
		printf("*** error: -c=, -C= or -t= must be specified\n");
		Usage();
		return ERR_PARAM;
	}

	if (((cycleUs != -1) || (cycleClk != -1)) && (test != -1)) {
		printf("*** error: only one option of -c=, -C= or -t= possible\n");
		return ERR_PARAM;
	}

	if (((cycleUs != -1) && (pulseClk != -1))) {
		printf("*** error: illegal parameter combination -c= with -P=\n");
		return ERR_PARAM;
	}

	if (((cycleClk != -1) && (pulseUs != -1))) {
		printf("*** error: illegal parameter combination -C= with -p=\n");
		return ERR_PARAM;
	}

	/*----------------------+
	|  open path            |
	+----------------------*/
	if ((G_path = M_open(device)) < 0) {
		return PrintError("open");
	}

	printf("system clock frequency: %dHz\n", sysFreq);

	/*----------------------+
	|  set period + pulse   |
	+----------------------*/
	/* cycle [us] OR [clocks] */
	if ((cycleUs != -1) || (cycleClk != -1)) {

		G_verbose = 1;

		/* cycle [us] */
		if (cycleUs != -1) {

			if (pulseUs == -1)
				/* default pulse [us] */
				pulseUs = cycleUs / 2;

			/* compute cycle/pulse [clocks] */
			cycleClk = Time2Clock(sysFreq, cycleUs);
			pulseClk = Time2Clock(sysFreq, pulseUs);
		}
		/* cycle [clocks] */
		else {
			if( pulseClk == -1)
				/* default pulse [clocks] */
				pulseClk = cycleClk / 2;
		}

		if (ConfigPwm(sysFreq, cycleClk, pulseClk))
			goto ABORT;
	}

	/*----------------------+
	|  PWM test             |
	+----------------------*/
	if(test != -1){
		loopcnt = 0;
		run = 1;
		do {
			G_cycleClkNibble = -1;
			G_pulseClkNibble = -1;

			loopcnt++;

			switch (test){
			/* sweep cycle length from min to max with 50% pulse length */
			case 1:
				printf("=== pass %d === : sweep cycle length from min..[%d]..max with 50%% pulse length, delay=%d\n",
					loopcnt, step, delay);
				for(n = 0; n <= 0x10000; n += step){

					/* cycle range: 2..0xffff */
					if (n == 0){
						cycleClk = 2;
					}
					else {
						cycleClk = n - 1;
						if (cycleClk <= 2)
							continue;
					}

					/* compute pulse [clocks] */
					pulseClk = cycleClk / 2;

					if (ConfigPwm(sysFreq, cycleClk, pulseClk))
						goto ABORT;

					/* repeat until keypress */
					if (UOS_KeyPressed() != -1)
						goto CLEANUP;

					if (delay)
						UOS_Delay(delay);
				}
				break;

			/*  sweep pulse length from min to max with max cycle length */
			case 2:
				printf("=== pass %d === : sweep pulse length from min..[%d]..max with max cycle length, delay=%d\n",
					loopcnt, step, delay);
				cycleClk = 0xffff;
				if (ConfigPwm(-1, cycleClk, -1))
					goto ABORT;

				for (n=0; n <= 0x10000; n += step) {

					/* pulse range: 0..0xffff */
					if(n == 0)
						pulseClk = 0;
					else{
						pulseClk = n - 1;
						if(pulseClk == 0)
							continue;
					}

					if (ConfigPwm(-1, -1, pulseClk))
						goto ABORT;

					PrintPwmSetting(sysFreq, cycleClk, pulseClk);

					/* repeat until keypress */
					if (UOS_KeyPressed() != -1)
						goto CLEANUP;

					if (delay)
						UOS_Delay(delay);
				}
				break;

			default:
				printf("*** error: illegal parameter test=%d\n", test);
				return ERR_PARAM;
			}

			/* abort after n turns */
			if (abort && (loopcnt == abort))
				run = 0;
					
		} while (run);
	}

	/*----------------------+
	|  cleanup              |
	+----------------------*/
CLEANUP:
	ret=ERR_OK;
	
ABORT:
	if (M_close(G_path) < 0)
		ret = PrintError("close");

	return ret;
}

/***************************************************************************/
/** Print MDIS error message
 *
 *  \param info       \IN  info string
 *
 *  \return           ERR_FUNC
 */
static int32 PrintError(char *info)
{
	printf("*** can't %s: %s\n", info, M_errstring (UOS_ErrnoGet()));
	return ERR_FUNC;
}

/***************************************************************************/
/** Compute clock from time
 *
 *  \param sysFreq    \IN  system clock frequency [Hz]
 *  \param timeUs     \IN  time [us]
 *
 *  \return           clock
 */
static int32 Time2Clock(int32 sysFreq, int32 timeUs)
{
	int32	clock;

	clock = timeUs * (sysFreq / 1000000);
	
	return clock;
}

/**************************** ConfigPwm **************************/
/** Configure PWM generator
*
*  \param sysFreq      \IN  system clock frequency [Hz] (or -1)
*  \param cycleClk     \IN  cycle length [clocks] (or -1)
*  \param pulseClk     \IN  pulse length [clocks] (or -1)
*
*  \return             success (0) or error code
*/
static int32 ConfigPwm(int32 sysFreq, int32 cycleClk, int32 pulseClk)
{
	int32 read;

	if (cycleClk != -1){
		if ((cycleClk > 0xffff) || (cycleClk == 0)) {
			printf("*** error: cycleClk=%d not in range 1..65535\n", cycleClk);
			return ERR_PARAM;
		}

		if ((M_setstat(G_path, Z061_PERIOD, cycleClk)) < 0)
			return PrintError("setstat Z061_PERIOD");

		if (G_verify != -1) {
			if ((M_getstat(G_path, Z061_PERIOD, &read)) < 0)
				return PrintError("getstat Z061_PERIOD");

			if (read != cycleClk) {
				printf("*** error: read cycleClk=0x%x differs from set cycleClk=0x%x\n",
					read, cycleClk);
				if (G_verify == 0)
					return ERR_FUNC;
			}
		}
	}

	if (pulseClk != -1) {
		if (pulseClk > 0xffff) {
			printf("*** error: pulseClk=%d not in range 0..65535\n", pulseClk);
			return ERR_PARAM;
		}
		if ((M_setstat(G_path, Z061_PULSE, pulseClk)) < 0)
			return PrintError("setstat Z061_PULSE");

		if (G_verify != -1) {
			if ((M_getstat(G_path, Z061_PULSE, &read)) < 0)
				return PrintError("getstat Z061_PULSE");

			if (read != pulseClk) {
				printf("*** error: read pulseClk=0x%x differs from set pulseClk=0x%x\n",
					read, pulseClk);
			if (G_verify == 0)
				return ERR_FUNC;
			}
		}
	}

	if(sysFreq != -1)
		PrintPwmSetting(sysFreq, cycleClk, pulseClk);

	return ERR_OK;
}

/**************************** PrintPwmSetting **************************/
/** Print PWM setting
*
*  \param sysFreq      \IN  system clock frequency [Hz]
*  \param cycleClk     \IN  cycle length in clocks
*  \param pulseClk     \IN  pulse length in clocks
*/
static void PrintPwmSetting(int32 sysFreq, int32 cycleClk, int32 pulseClk)
{
	int32  freq, duty;
	float  cycleUs, pulseUs;
	char   print = 0;

	freq = (((sysFreq * 10) / cycleClk) + 5) / 10;
	duty = (((pulseClk * 1000) / cycleClk) + 5) / 10;

	cycleUs = (((cycleClk * 1000000.0) / (float)sysFreq));
	pulseUs = (((pulseClk * 1000000.0) / (float)sysFreq));

	/* always print each setting */
	if(G_verbose){
		print = 1;
	}
	/* print only changes in MS nibble of cycle or pulse length */
	else {
		if (G_cycleClkNibble == -1) {
			G_cycleClkNibble++;
			G_pulseClkNibble++;
			print = 1;
		}

		if ((cycleClk >> 12) > G_cycleClkNibble) {
			G_cycleClkNibble = cycleClk >> 12;
			print = 1;
		}
		if ((pulseClk >> 12) > G_pulseClkNibble) {
			G_pulseClkNibble = pulseClk >> 12;
			print = 1;
		}
	}

	if( print )
		printf("PWM freq=%8dHz, duty=%3d%%, cycleUs=%8.2fus, pulseUs=%8.2fus, cycleClk=%5d, pulseClk=%5d\n",
			freq, duty, cycleUs, pulseUs, cycleClk, pulseClk );
}
