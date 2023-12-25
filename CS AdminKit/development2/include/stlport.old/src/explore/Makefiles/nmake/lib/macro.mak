# -*- makefile -*- Time-stamp: <04/03/22 22:17:22 ptr>
# $Id: macro.mak,v 1.4.2.2 2004/09/21 20:10:01 dums Exp $

RELEASE_SUFFIX = r
DBG_SUFFIX = d
STLDBG_SUFFIX = stl$(DBG_SUFFIX)

# default prefix: none
!ifndef LIB_NAME_PREFIX
LIB_NAME_PREFIX =
!endif

# Shared libraries:

# By Damir
# SO_NAME_BASE    = $(LIB_NAME_PREFIX)$(LIBNAME)_$(RELEASE_SUFFIX)$(MAJOR)$(MINOR)
SO_NAME_BASE    = $(LIB_NAME_PREFIX)$(LIBNAME)
SO_NAME         = $(SO_NAME_BASE).$(SO)
LIB_NAME        = $(SO_NAME_BASE).$(LIBEXT)
EXP_NAME        = $(SO_NAME_BASE).$(EXP)
PDB_NAME        = $(LIBNAME).pdb
RES_NAME        = $(LIBNAME).res

SO_NAME_OUT    = $(OUTPUT_DIR)\$(SO_NAME)
LIB_NAME_OUT    = $(OUTPUT_DIR)\$(LIB_NAME)
EXP_NAME_OUT    = $(OUTPUT_DIR)\$(EXP_NAME)
PDB_NAME_OUT    = $(OUTPUT_DIR)\$(PDB_NAME)
RES_NAME_OUT    = $(OUTPUT_DIR)\$(RES_NAME)

# By Damir
# SO_NAME_DBG_BASE = $(LIB_NAME_PREFIX)$(LIBNAME)_$(DBG_SUFFIX)$(MAJOR)$(MINOR)
SO_NAME_DBG_BASE = $(LIB_NAME_PREFIX)$(LIBNAME)
SO_NAME_DBG     = $(SO_NAME_DBG_BASE).$(SO)
LIB_NAME_DBG    = $(SO_NAME_DBG_BASE).$(LIBEXT)
EXP_NAME_DBG    = $(SO_NAME_DBG_BASE).$(EXP)

SO_NAME_OUT_DBG    = $(OUTPUT_DIR_DBG)\$(SO_NAME_DBG)
LIB_NAME_OUT_DBG    = $(OUTPUT_DIR_DBG)\$(LIB_NAME_DBG)
EXP_NAME_OUT_DBG    = $(OUTPUT_DIR_DBG)\$(EXP_NAME_DBG)
PDB_NAME_OUT_DBG    = $(OUTPUT_DIR_DBG)\$(PDB_NAME)
RES_NAME_OUT_DBG    = $(OUTPUT_DIR_DBG)\$(RES_NAME)

# By Damir
# SO_NAME_STLDBG_BASE = $(LIB_NAME_PREFIX)$(LIBNAME)_$(STLDBG_SUFFIX)$(MAJOR)$(MINOR)
SO_NAME_STLDBG_BASE = $(LIB_NAME_PREFIX)$(LIBNAME)
SO_NAME_STLDBG     = $(SO_NAME_STLDBG_BASE).$(SO)
LIB_NAME_STLDBG    = $(SO_NAME_STLDBG_BASE).$(LIBEXT)
EXP_NAME_STLDBG    = $(SO_NAME_STLDBG_BASE).$(EXP)

SO_NAME_OUT_STLDBG   = $(OUTPUT_DIR_STLDBG)\$(SO_NAME_STLDBG)
LIB_NAME_OUT_STLDBG    = $(OUTPUT_DIR_STLDBG)\$(LIB_NAME_STLDBG)
EXP_NAME_OUT_STLDBG    = $(OUTPUT_DIR_STLDBG)\$(EXP_NAME_STLDBG)
PDB_NAME_OUT_STLDBG    = $(OUTPUT_DIR_STLDBG)\$(PDB_NAME)
RES_NAME_OUT_STLDBG    = $(OUTPUT_DIR_STLDBG)\$(RES_NAME)

# Static libraries:
A_NAME = $(LIB_NAME_PREFIX)$(LIBNAME)_static_$(RELEASE_SUFFIX)$(MAJOR)$(MINOR).$(ARCH)
A_NAME_OUT = $(OUTPUT_DIR_A)\$(A_NAME)
A_PDB_NAME_OUT = $(OUTPUT_DIR_A)\$(PDB_NAME)

A_NAME_DBG = $(LIB_NAME_PREFIX)$(LIBNAME)_static_$(DBG_SUFFIX)$(MAJOR)$(MINOR).$(ARCH)
A_NAME_OUT_DBG = $(OUTPUT_DIR_A_DBG)\$(A_NAME_DBG)
A_PDB_NAME_OUT_DBG = $(OUTPUT_DIR_A_DBG)\$(PDB_NAME)

A_NAME_STLDBG = $(LIB_NAME_PREFIX)$(LIBNAME)_static_$(STLDBG_SUFFIX)$(MAJOR)$(MINOR).$(ARCH)
A_NAME_OUT_STLDBG = $(OUTPUT_DIR_A_STLDBG)\$(A_NAME_STLDBG)
A_PDB_NAME_OUT_STLDBG = $(OUTPUT_DIR_A_STLDBG)\$(PDB_NAME)

