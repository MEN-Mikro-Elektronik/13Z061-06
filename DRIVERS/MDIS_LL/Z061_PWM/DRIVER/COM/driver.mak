#***************************  M a k e f i l e  *******************************
#
#         Author: rla
#          $Date: 2006/01/30 12:19:05 $
#      $Revision: 1.1 $
#
#    Description: Makefile definitions for the Z61 driver
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: driver.mak,v $
#   Revision 1.1  2006/01/30 12:19:05  rla
#   Initial Revision
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2006 by MEN mikro elektronik GmbH, Nuernberg, Germany
#*****************************************************************************

MAK_NAME=z61

MAK_SWITCH=$(SW_PREFIX)MAC_MEM_MAPPED

MAK_LIBS=$(LIB_PREFIX)$(MEN_LIB_DIR)/desc$(LIB_SUFFIX)	\
         $(LIB_PREFIX)$(MEN_LIB_DIR)/oss$(LIB_SUFFIX)	\
         $(LIB_PREFIX)$(MEN_LIB_DIR)/dbg$(LIB_SUFFIX)	\


MAK_INCL=$(MEN_INC_DIR)/z61_drv.h	\
         $(MEN_INC_DIR)/men_typs.h	\
         $(MEN_INC_DIR)/oss.h		\
         $(MEN_INC_DIR)/mdis_err.h	\
         $(MEN_INC_DIR)/maccess.h	\
         $(MEN_INC_DIR)/desc.h		\
         $(MEN_INC_DIR)/mdis_api.h	\
         $(MEN_INC_DIR)/mdis_com.h	\
         $(MEN_INC_DIR)/modcom.h	\
         $(MEN_INC_DIR)/ll_defs.h	\
         $(MEN_INC_DIR)/ll_entry.h	\
         $(MEN_INC_DIR)/dbg.h		\
         $(MEN_MOD_DIR)/z61_int.h

MAK_INP1=z61_drv$(INP_SUFFIX)
MAK_INP2=

MAK_INP=$(MAK_INP1) \
        $(MAK_INP2)
