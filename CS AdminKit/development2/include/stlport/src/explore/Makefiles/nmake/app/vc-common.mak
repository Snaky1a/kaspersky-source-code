# -*- makefile -*- Time-stamp: <03/09/28 17:34:35 ptr>
# $Id: vc-common.mak,v 1.1.2.5 2004/10/31 14:14:57 dums Exp $

!ifndef LDLIBS
LDLIBS =
!endif

LDSEARCH = $(LDSEARCH) /LIBPATH:"$(MSVC_LIB_DIR)"

!ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
OPT_REL = $(OPT_REL) /MT
OPT_DBG = $(OPT_DBG) /MTd
OPT_STLDBG = $(OPT_STLDBG) /MTd
!else
OPT_REL = $(OPT_REL) /MD
OPT_DBG = $(OPT_DBG) /MDd
OPT_STLDBG = $(OPT_STLDBG) /MDd
!endif

!ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
OPT_STATIC_REL = $(OPT_STATIC_REL) /MD
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MDd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MDd
!else
OPT_STATIC_REL = $(OPT_STATIC_REL) /MT
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MTd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MTd
!endif

LDFLAGS_REL = $(LDFLAGS_REL) $(LDSEARCH)
LDFLAGS_A_REL = $(LDFLAGS_A_REL) $(LDSEARCH)
LDFLAGS_DBG = $(LDFLAGS_DBG) $(LDSEARCH)
LDFLAGS_STLDBG = $(LDFLAGS_STLDBG) $(LDSEARCH)
