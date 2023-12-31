# -*- Makefile -*- Time-stamp: <03/10/26 17:39:09 ptr>
# $Id: nmake-vc-common.mak,v 1.1.2.3 2004/10/04 19:48:46 dums Exp $

SRCROOT=.

STLPORT_INCLUDE_DIR = ../../stlport
!include Makefile.inc

!ifdef STLP_BUILD_FORCE_STATIC_RUNTIME
DEFS_REL = /D_STLP_USE_DYNAMIC_LIB
DEFS_DBG = /D_STLP_USE_DYNAMIC_LIB /D_STLP_USE_MALLOC=1
DEFS_STLDBG = /D_STLP_USE_DYNAMIC_LIB  /D_STLP_USE_MALLOC=1
!endif
!ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
DEFS_STATIC_REL = /D_STLP_USE_STATIC_LIB 
DEFS_STATIC_DBG = /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC=1
DEFS_STATIC_STLDBG = /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC=1
!endif

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /FI "vc_warning_disable.h"

!ifdef STLP_BUILD_BOOST_PATH
INCLUDES=$(INCLUDES) /I "$(STLP_BUILD_BOOST_PATH)"
!endif

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)
RC_FLAGS_REL = /d COMP=$(COMPILER_NAME)
RC_FLAGS_DBG = /d COMP=$(COMPILER_NAME) /d BUILD=_DEBUG
RC_FLAGS_STLDBG = /d COMP=$(COMPILER_NAME) /d BUILD=_STLDEBUG
OPT_STLDBG = /Zm800

!include $(SRCROOT)/Makefiles/nmake/top.mak
