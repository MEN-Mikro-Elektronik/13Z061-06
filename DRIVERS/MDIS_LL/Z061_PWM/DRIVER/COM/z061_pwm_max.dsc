#************************** MDIS4 device descriptor *************************
#
#        Author: rla
#         $Date: 2006/01/30 12:19:07 $
#     $Revision: 1.1 $
#
#   Description: Metadescriptor for Z61 PWM
#
#****************************************************************************

pwm_1  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61         # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  0                  # used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	debug levels (optional)
	#   this keys have only effect on debug drivers
	#------------------------------------------------------------------------
    DEBUG_LEVEL      = U_INT32  0xc0008000  # LL driver
    DEBUG_LEVEL_MK   = U_INT32  0xc0008000  # MDIS kernel
    DEBUG_LEVEL_OSS  = U_INT32  0xc0008000  # OSS calls
    DEBUG_LEVEL_DESC = U_INT32  0xc0008000  # DESC calls
    DEBUG_LEVEL_MBUF = U_INT32  0xc0008000  # MBUF calls

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

pwm_2  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61         # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  2                  # used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	debug levels (optional)
	#   this keys have only effect on debug drivers
	#------------------------------------------------------------------------
    DEBUG_LEVEL      = U_INT32  0xc0008000  # LL driver
    DEBUG_LEVEL_MK   = U_INT32  0xc0008000  # MDIS kernel
    DEBUG_LEVEL_OSS  = U_INT32  0xc0008000  # OSS calls
    DEBUG_LEVEL_DESC = U_INT32  0xc0008000  # DESC calls
    DEBUG_LEVEL_MBUF = U_INT32  0xc0008000  # MBUF calls

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

pwm_3  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61         # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  2                  # used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	debug levels (optional)
	#   this keys have only effect on debug drivers
	#------------------------------------------------------------------------
    DEBUG_LEVEL      = U_INT32  0xc0008000  # LL driver
    DEBUG_LEVEL_MK   = U_INT32  0xc0008000  # MDIS kernel
    DEBUG_LEVEL_OSS  = U_INT32  0xc0008000  # OSS calls
    DEBUG_LEVEL_DESC = U_INT32  0xc0008000  # DESC calls
    DEBUG_LEVEL_MBUF = U_INT32  0xc0008000  # MBUF calls

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

pwm_4  {
	#------------------------------------------------------------------------
	#	general parameters (don't modify)
	#------------------------------------------------------------------------
    DESC_TYPE        = U_INT32  1           # descriptor type (1=device)
    HW_TYPE          = STRING   Z61         # hardware name of device

	#------------------------------------------------------------------------
	#	reference to base board
	#------------------------------------------------------------------------
    BOARD_NAME    = STRING   chameleon_pcitbl_1 # device name of baseboard
    DEVICE_SLOT   = U_INT32  3                  # used slot on baseboard (0..n)

	#------------------------------------------------------------------------
	#	debug levels (optional)
	#   this keys have only effect on debug drivers
	#------------------------------------------------------------------------
    DEBUG_LEVEL      = U_INT32  0xc0008000  # LL driver
    DEBUG_LEVEL_MK   = U_INT32  0xc0008000  # MDIS kernel
    DEBUG_LEVEL_OSS  = U_INT32  0xc0008000  # OSS calls
    DEBUG_LEVEL_DESC = U_INT32  0xc0008000  # DESC calls
    DEBUG_LEVEL_MBUF = U_INT32  0xc0008000  # MBUF calls

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
