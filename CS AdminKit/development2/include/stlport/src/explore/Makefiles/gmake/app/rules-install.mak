# -*- makefile -*- Time-stamp: <04/07/25 17:58:50 ptr>
# $Id: rules-install.mak,v 1.1.2.4 2004/10/13 10:11:56 ptr Exp $

install:	install-release-shared install-dbg-shared install-stldbg-shared

# The program name to be installed will be the same as compiled name,
# but it will be a bit altered in case of installation debug and/or
# stlport-debug program in the same catalog as 'release' program.

INSTALL_PRGNAME := ${PRGNAME}${EXE}

ifeq (${INSTALL_BIN_DIR},${INSTALL_BIN_DIR_DBG})
INSTALL_PRGNAME_DBG := ${PRGNAME}g${EXE}
else
INSTALL_PRGNAME_DBG := ${INSTALL_PRGNAME}
endif

ifeq (${INSTALL_BIN_DIR},${INSTALL_BIN_DIR_STLDBG})
INSTALL_PRGNAME_STLDBG := ${PRGNAME}stlg${EXE}
else
INSTALL_PRGNAME_STLDBG := ${INSTALL_PRGNAME}
endif

ifeq (${INSTALL_BIN_DIR_DBG},${INSTALL_BIN_DIR_STLDBG})
INSTALL_PRGNAME_DBG := ${PRGNAME}g${EXE}
INSTALL_PRGNAME_STLDBG := ${PRGNAME}stlg${EXE}
endif

install-release-shared: release-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG} $(INSTALL_BIN_DIR)/${INSTALL_PRGNAME}

install-dbg-shared: dbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_DBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_DBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_DBG} $(INSTALL_BIN_DIR_DBG)/${INSTALL_PRGNAME_DBG}

install-stldbg-shared: stldbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_STLDBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_STLDBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_STLDBG} $(INSTALL_BIN_DIR_STLDBG)/${INSTALL_PRGNAME_STLDBG}
