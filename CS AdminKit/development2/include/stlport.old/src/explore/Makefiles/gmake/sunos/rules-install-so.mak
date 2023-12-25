# -*- makefile -*- Time-stamp: <03/07/10 13:22:04 ptr>
# $Id: rules-install-so.mak,v 1.1.2.1 2004/09/24 10:54:44 ptr Exp $

INSTALL_TAGS ?= install-release-shared install-dbg-shared install-stldbg-shared

PHONY += install $(INSTALL_TAGS)

install:	$(INSTALL_TAGS)

install-release-shared:	release-shared
	@if [ -h $(INSTALL_LIB_DIR)/${SO_NAME} ] ; then \
	  rm $(INSTALL_LIB_DIR)/${SO_NAME}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR)/${SO_NAMEx} ] ; then \
	  rm $(INSTALL_LIB_DIR)/${SO_NAMEx}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR)/${SO_NAMExx} ] ; then \
	  rm $(INSTALL_LIB_DIR)/${SO_NAMExx}; \
	fi
	@if [ -f $(INSTALL_LIB_DIR)/${SO_NAMExxx} ] ; then \
	  rm $(INSTALL_LIB_DIR)/${SO_NAMExxx}; \
	fi
	$(INSTALL_SO) ${SO_NAME_OUTxxx} $(INSTALL_LIB_DIR)
	(cd $(INSTALL_LIB_DIR) && \
	 { ln -s ${SO_NAMExxx} ${SO_NAMExx}; \
	   ln -s ${SO_NAMExx} ${SO_NAMEx}; \
	   ln -s ${SO_NAMEx} ${SO_NAME}; } )

install-dbg-shared:	dbg-shared
	@if [ -h $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBG} ] ; then \
	  rm $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBG}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGx} ] ; then \
	  rm $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGx}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGxx} ] ; then \
	  rm $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGxx}; \
	fi
	@if [ -f $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGxxx} ] ; then \
	  rm $(INSTALL_LIB_DIR_DBG)/${SO_NAME_DBGxxx}; \
	fi
	$(INSTALL_SO) ${SO_NAME_OUT_DBGxxx} $(INSTALL_LIB_DIR_DBG)
	(cd $(INSTALL_LIB_DIR_DBG) && \
	 { ln -s ${SO_NAME_DBGxxx} ${SO_NAME_DBGxx}; \
	   ln -s ${SO_NAME_DBGxx} ${SO_NAME_DBGx}; \
	   ln -s ${SO_NAME_DBGx} ${SO_NAME_DBG}; } )

install-stldbg-shared:	stldbg-shared
	@if [ -h $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBG} ] ; then \
	  rm $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBG}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGx} ] ; then \
	  rm $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGx}; \
	fi
	@if [ -h $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGxx} ] ; then \
	  rm $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGxx}; \
	fi
	@if [ -f $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGxxx} ] ; then \
	  rm $(INSTALL_LIB_DIR_STLDBG)/${SO_NAME_STLDBGxxx}; \
	fi
	$(INSTALL_SO) ${SO_NAME_OUT_STLDBGxxx} $(INSTALL_LIB_DIR_STLDBG)
	(cd $(INSTALL_LIB_DIR_STLDBG) && \
	 { ln -s ${SO_NAME_STLDBGxxx} ${SO_NAME_STLDBGxx}; \
	   ln -s ${SO_NAME_STLDBGxx} ${SO_NAME_STLDBGx}; \
	   ln -s ${SO_NAME_STLDBGx} ${SO_NAME_STLDBG}; } )
