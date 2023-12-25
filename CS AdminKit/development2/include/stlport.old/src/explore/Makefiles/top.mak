# Time-stamp: <04/03/09 20:14:25 ptr>
# $Id: top.mak,v 1.2.2.1 2004/06/22 19:39:06 dums Exp $

.SUFFIXES:
.SCCS_GET:
.RCS_GET:

PHONY ?=

.PHONY: $(PHONY)

RULESBASE ?= $(SRCROOT)/Makefiles

ALL_TAGS = release-shared
#	dbg-shared	stldbg-shared

all:	dirs $(ALL_TAGS)

all-static:	release-static	dbg-static	stldbg-static
all-shared:	release-shared	dbg-shared	stldbg-shared

# include file, generated by configure, if available
-include ${RULESBASE}/config.mak
# define what make clone we use
include ${RULESBASE}/make.mak
# identify OS and build date
include ${RULESBASE}/$(USE_MAKE)/sysid.mak
# OS-specific definitions, like ar, ln, install, etc.
include ${RULESBASE}/$(USE_MAKE)/$(OSNAME)/sys.mak
# compiler, compiler options
include ${RULESBASE}/$(USE_MAKE)/$(COMPILER_NAME).mak
# rules to make dirs for targets
include ${RULESBASE}/$(USE_MAKE)/targetdirs.mak
# extern libraries
include ${RULESBASE}/$(USE_MAKE)/$(OSNAME)/extern.mak

# os-specific local rules
-include specific.mak

# derive common targets (*.o, *.d),
# build rules (including output catalogs)
include ${RULESBASE}/$(USE_MAKE)/targets.mak
# dependency
include ${RULESBASE}/$(USE_MAKE)/depend.mak

# general clean
include ${RULESBASE}/clean.mak

# if target is library, rules for library
ifdef LIBNAME
include ${RULESBASE}/$(USE_MAKE)/lib/top.mak
endif

# if target is program, rules for executable
ifdef PRGNAME
include ${RULESBASE}/$(USE_MAKE)/app/top.mak
endif
