# Microsoft Developer Studio Project File - Name="klsp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=klsp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "klsp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "klsp.mak" CFG="klsp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "klsp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "klsp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "klsp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gz /W3 /WX /Oy /Gy /D "WIN32" /Oxs /c
# ADD CPP /nologo /Gz /W3 /Oy /Gy /I "$(BASEDIR)\inc" /I "$(BASEDIR)\src\network\inc" /I "..\..\..\KLSDK" /FI"$(BASEDIR)\inc\warning.h" /D WIN32=100 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D FPO=1 /D "_IDWBUILD" /D "NDEBUG" /D _DLL=1 /D _X86_=1 /D $(CPU)=1 /D "HOOK_MODE_LOAD" /Oxs /Zel -cbstring /QIfdiv- /QIf /GF /c
# SUBTRACT CPP /WX /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "$(BASEDIR)\inc" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /machine:IX86
# ADD LINK32 int64.lib ntoskrnl.lib hal.lib tdi.lib /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry" /machine:IX86 /nodefaultlib /out:"Release\klsp.sys" /libpath:"$(BASEDIR)\lib\i386\free" /libpath:"..\..\Release\\" /driver /debug:notmapped,MINIMAL /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /FORCE:MULTIPLE /OPT:REF /OPTIDATA /align:0x20 /osversion:4.00 /subsystem:native
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gz /W3 /Zi /Od /D "WIN32" /YX /FD /c
# ADD CPP /nologo /Gz /W3 /Zi /Oi /Gy /I "$(BASEDIR)\inc" /I "$(BASEDIR)\src\network\inc" /I "..\..\..\KLSDK" /FI"$(BASEDIR)\inc\warning.h" /D "__CPP" /D "_DEBUG" /D WIN32=100 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DBG=1 /D DEVL=1 /D FPO=0 /D "NDEBUG" /D _DLL=1 /D _X86_=1 /D $(CPU)=1 /D "HOOK_MODE_LOAD" /FR /FD /Zel -cbstring /QIfdiv- /QIf /GF /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /i "$(BASEDIR)\inc"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"objchk\i386\klsp.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /machine:IX86
# ADD LINK32 int64.lib ntoskrnl.lib hal.lib tdi.lib /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry" /incremental:no /debug /debugtype:both /machine:IX86 /nodefaultlib /out:"debug\klsp.sys" /libpath:"$(BASEDIR)\lib\i386\checked" /libpath:"..\..\debug" /driver /debug:notmapped,FULL /IGNORE:4006,4001,4037,4039,4065,4078,4087,4088,4089,4096 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /FORCE:MULTIPLE /OPT:REF /OPTIDATA /align:0x20 /osversion:4.00 /subsystem:native
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\debug\klsp.sys
TargetName=klsp
SOURCE="$(InputPath)"
PostBuild_Cmds=PostBuild.cmd Debug $(TargetPath) $(TargetName)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "klsp - Win32 Release"
# Name "klsp - Win32 Debug"
# Begin Group "source"

# PROP Default_Filter ""
# Begin Group "Common Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_Filter.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\klinplugin.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Common Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\klinplugin.h
# End Source File
# End Group
# Begin Group "Plugins"

# PROP Default_Filter ""
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ftp_parser.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SygCheck.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\tdi_parser.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\test.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ftp_parser.h
# End Source File
# Begin Source File

SOURCE=..\SygCheck.h
# End Source File
# Begin Source File

SOURCE=..\tdi_parser.h
# End Source File
# Begin Source File

SOURCE=..\test.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\pluginit.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "includes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\g_precomp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_list.h
# End Source File
# Begin Source File

SOURCE=..\pluginit.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# End Group
# Begin Group "KLSDK source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_buffer.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_file.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_list.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_lock.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_object.cpp

!IF  "$(CFG)" == "klsp - Win32 Release"

!ELSEIF  "$(CFG)" == "klsp - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "KLSDK include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_file.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_lock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kl_vector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\kldef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KLSDK\klstatus.h
# End Source File
# End Group
# End Target
# End Project
