# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id: icc.mak,v 1.1 2004/02/12 09:10:19 ptr Exp $


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

OPT += -KPIC

ifeq ($(OSNAME),linux)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

