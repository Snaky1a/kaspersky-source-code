# Microsoft Developer Studio Project File - Name="KLE_SYS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KLE_SYS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KLE_SYS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KLE_SYS.mak" CFG="KLE_SYS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KLE_SYS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KLE_SYS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/AVP32/KLE_SYS", MDEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KLE_SYS - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /G3 /Gz /MT /W3 /Z7 /O2 /I "..\\" /I "..\GKNT" /I "$(DRIVERWORKS)\include" /I "$(DRIVERWORKS)\source" /I "$(BASEDIR)\inc" /I "i386\\" /I "." /D FPO=1 /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D NTVERSION=400 /D _X86_=1 /D i386=1 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D "NDEBUG" /D _DLL=1 /D GDATA=G /D "NT_DRIVER" /YX /FD /Zel -cbstring /QIfdiv- /QIf /GF /Oxs /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "$(BASEDIR)\inc" /d "NDEBUG" /d WIN32_LEAN_AND_MEAN=1
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 int64.lib ntoskrnl.lib hal.lib vdw.lib /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry@8" /subsystem:windows /pdb:none /map:"..\Release\KLE_SYS.map" /machine:I386 /nodefaultlib /out:"..\release\KLE_SYS.sys" /libpath:"$(BASEDIR)\lib\i386\free" /libpath:"$(DRIVERWORKS)\lib\i386\free" -MERGE:_PAGE=PAGE -MERGE:_TEXT=.text -SECTION:INIT,d -OPT:REF -FORCE:MULTIPLE -RELEASE -FULLBUILD -IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096 -MERGE:.rdata=.text -optidata -driver -align:0x20 -osversion:4.00 -subsystem:native,4.00 -debug:notmapped,MINIMAL /MAPINFO:LINES
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
TargetPath=\Work\avp32\release\KLE_SYS.sys
SOURCE="$(InputPath)"
PostBuild_Desc=Finalizing...
PostBuild_Cmds=rebase -b 0x10000 -x . -a E:$(TargetPath)	sync
# End Special Build Tool

!ELSEIF  "$(CFG)" == "KLE_SYS - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /G3 /Gz /MTd /W3 /Zi /Od /I "..\\" /I "..\GKNT" /I "$(DRIVERWORKS)\include" /I "$(DRIVERWORKS)\source" /I "$(BASEDIR)\inc" /I "i386\\" /I "." /D "_DEBUG" /D DBG=1 /D FPO=0 /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D NTVERSION=400 /D _X86_=1 /D i386=1 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D _DLL=1 /D GDATA=G /D "NT_DRIVER" /FD /Zel -cbstring /QIfdiv- /QIf /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "$(BASEDIR)\inc" /d "_DEBUG" /d WIN32_LEAN_AND_MEAN=1
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 int64.lib ntoskrnl.lib hal.lib vdw.lib chkesp.obj /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry@8" /subsystem:windows /debug /machine:I386 /nodefaultlib /out:"..\debug\KLE_SYS.sys" /libpath:"$(BASEDIR)\lib\i386\checked" /libpath:"$(DRIVERWORKS)\lib\i386\checked" -MERGE:_PAGE=PAGE -MERGE:_TEXT=.text -SECTION:INIT,d -OPT:REF -FORCE:MULTIPLE -RELEASE -FULLBUILD -IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096,4075 -MERGE:.rdata=.text -optidata -driver -align:0x20 -osversion:4.00 -subsystem:native,4.00 -debug:notmapped,FULL
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Special Build Tool
TargetPath=\Work\avp32\debug\KLE_SYS.sys
SOURCE="$(InputPath)"
PostBuild_Desc=Finalizing...
PostBuild_Cmds=$(SOFTICE)\nmsym /TRANSLATE /LOAD $(TargetPath)	rebase -b 0x10000 -x . -a E:$(TargetPath)	sync
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "KLE_SYS - Win32 Release"
# Name "KLE_SYS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\KLE\KLE_IPL.cpp
# End Source File
# Begin Source File

SOURCE=.\KLE_SYS.cpp
# End Source File
# Begin Source File

SOURCE=.\KLE_SYS.rc
# End Source File
# Begin Source File

SOURCE=.\KLE_SYSDev.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "KLE_SYS - Win32 Release"

!ELSEIF  "$(CFG)" == "KLE_SYS - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sysio.cpp
# End Source File
# Begin Source File

SOURCE=.\Syssign.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\CommonFiles\_avpio.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Stuff\_carray.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\ScanAPI\Avp_msg.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\ScanAPI\Avpioctl.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\ScanAPI\BaseAPI.h
# End Source File
# Begin Source File

SOURCE=.\function.h
# End Source File
# Begin Source File

SOURCE=..\Gknt\Gkapi.h
# End Source File
# Begin Source File

SOURCE=..\KLE\KLE_IPL.h
# End Source File
# Begin Source File

SOURCE=.\KLE_SYS.h
# End Source File
# Begin Source File

SOURCE=.\KLE_SYSDev.h
# End Source File
# Begin Source File

SOURCE=..\KLE\KLEAPI.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\ScanAPI\RetFlags.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\ScanAPI\Scanobj.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Sysio.h
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Version\ver_avp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\KLE_SYS.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\KLE_SYS.ini
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Release\Property.lib
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Release\KLDTSer.lib
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Release\Sign.lib
# End Source File
# Begin Source File

SOURCE=..\..\CommonFiles\Release\SWM.lib
# End Source File
# End Target
# End Project
