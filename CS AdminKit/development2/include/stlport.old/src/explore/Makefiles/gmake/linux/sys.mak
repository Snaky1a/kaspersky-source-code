# Time-stamp: <04/03/03 15:49:24 ptr>
# $Id: sys.mak,v 1.2 2004/03/11 05:14:51 ptr Exp $

SO := so

ARCH := a
AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@

INSTALL := /usr/bin/install

INSTALL_SO := ${INSTALL} -c -m 0755
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755

