# -*- Makefile -*- Time-stamp: <04/03/30 14:53:15 ptr>
# $Id: nmake-vc-common.mak,v 1.1.2.7 2004/10/27 18:21:20 dums Exp $

SRCROOT=../../src/explore
STLPORT_DIR=../..

!include Makefile.inc

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /I "$(STLPORT_DIR)/src" /FI "vc_warning_disable.h"

!ifdef STLP_BUILD_BOOST_PATH
INCLUDES=$(INCLUDES) /I "$(STLP_BUILD_BOOST_PATH)"
!endif

DEFS=/D_STLP_NO_CUSTOM_IO /D_STLP_USE_AUTO_LINK /DCPPUNIT_MINI=1

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

!include $(SRCROOT)/Makefiles/nmake/top.mak
