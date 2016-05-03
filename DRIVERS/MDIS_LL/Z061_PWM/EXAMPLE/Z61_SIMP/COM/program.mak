#***************************  M a k e f i l e  *******************************
#
#         Author: rla
#          $Date: 2006/01/30 12:19:12 $
#      $Revision: 1.1 $
#
#    Description: Makefile definitions for the Z61 example program
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: program.mak,v $
#   Revision 1.1  2006/01/30 12:19:12  rla
#   Initial Revision
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2006 by MEN mikro elektronik GmbH, Nuernberg, Germany
#*****************************************************************************

MAK_NAME=z61_simp

MAK_LIBS=$(LIB_PREFIX)$(MEN_LIB_DIR)/mdis_api$(LIB_SUFFIX)	\
         $(LIB_PREFIX)$(MEN_LIB_DIR)/usr_oss$(LIB_SUFFIX)     \
         $(LIB_PREFIX)$(MEN_LIB_DIR)/usr_utl$(LIB_SUFFIX)     \

MAK_INCL=$(MEN_INC_DIR)/z61_drv.h	\
         $(MEN_INC_DIR)/men_typs.h	\
         $(MEN_INC_DIR)/mdis_api.h	\
         $(MEN_INC_DIR)/usr_utl.h	\
         $(MEN_INC_DIR)/usr_oss.h	\

MAK_INP1=z61_simp$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
