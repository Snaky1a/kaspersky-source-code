#
# DO NOT EDIT THIS FILE!!!  Edit .\sources. if you want to add a new source
# file to this component.  This file merely indirects to the real make file
# that is shared by all the components of NT
#

#!INCLUDE $(NTMAKEENV)\makefile.def


!IF DEFINED(_NT_TARGET_VERSION)
#!	IF $(_NT_TARGET_VERSION)>=0x501
!	IF $(_NT_TARGET_VERSION)>=0x600
!		INCLUDE $(NTMAKEENV)\makefile.def
!	ELSE
#               Only warn once per directory
!               INCLUDE $(NTMAKEENV)\makefile.plt
!               IF "$(BUILD_PASS)"=="PASS1"
!		    message BUILDMSG: Warning : Building the sample "$(MAKEDIR)" for downlevel build environments is temporarily disabled in WDK for Beta1.
!               ENDIF
!	ENDIF
!ELSE
!	INCLUDE $(NTMAKEENV)\makefile.def
!ENDIF
