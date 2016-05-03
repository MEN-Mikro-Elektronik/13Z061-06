#************************** MDIS4 device descriptor *************************
#
#        Author: rla
#         $Date: 2006/01/30 12:19:10 $
#     $Revision: 1.1 $
#
#   Description: Metadescriptor for Z61 PWM, swapped variant
#
#****************************************************************************

pwm_sw_1  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61_SW      # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  0           		# used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	device parameters
	#------------------------------------------------------------------------

	# PERIOD register initial value
	# range: 0..0xFFFF
	Z061_PERIOD_INIT = U_INT16 0

	# PULSE register initial value
	# range: 0..0xFFFF
	Z061_PULSE_INIT = U_INT16 0
}

pwm_sw_2  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61_SW      # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  1           		# used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	device parameters
	#------------------------------------------------------------------------

	# PERIOD register initial value
	# range: 0..0xFFFF
	Z061_PERIOD_INIT = U_INT16 0

	# PULSE register initial value
	# range: 0..0xFFFF
	Z061_PULSE_INIT = U_INT16 0
}

pwm_sw_3  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61_SW      # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  2           		# used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	device parameters
	#------------------------------------------------------------------------

	# PERIOD register initial value
	# range: 0..0xFFFF
	Z061_PERIOD_INIT = U_INT16 0

	# PULSE register initial value
	# range: 0..0xFFFF
	Z061_PULSE_INIT = U_INT16 0
}

pwm_sw_4  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61_SW      # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  3           		# used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	device parameters
	#------------------------------------------------------------------------

	# PERIOD register initial value
	# range: 0..0xFFFF
	Z061_PERIOD_INIT = U_INT16 0

	# PULSE register initial value
	# range: 0..0xFFFF
	Z061_PULSE_INIT = U_INT16 0
}
