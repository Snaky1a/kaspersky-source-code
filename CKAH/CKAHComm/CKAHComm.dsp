# Microsoft Developer Studio Project File - Name="CKAHComm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CKAHComm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CKAHComm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CKAHComm.mak" CFG="CKAHComm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CKAHComm - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CKAHComm - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Components/Windows/KAH/CKAHComm", PWUQAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CKAHComm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\temp\Release\CKAHComm"
# PROP Intermediate_Dir "..\..\..\..\temp\Release\CKAHComm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CKAHCOMM_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /O2 /I "../../../../Windows/Hook/" /I "../../../../CommonFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CKAHCOMM_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\..\CommonFiles" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib win32utils.lib FSDrvLib.lib rpcrt4.lib /nologo /base:"0x6A100000" /dll /pdb:"..\..\..\..\out\Release\CKAHComm.pdb" /debug /machine:I386 /out:"..\..\..\..\out\Release\CKAHComm.dll" /implib:"..\..\..\..\out\Release\CKAHComm.lib" /libpath:"../../../../CommonFiles/ReleaseDll" /libpath:"../../../../Out/Release"
# SUBTRACT LINK32 /pdb:none /pdbtype:<none>
# Begin Special Build Tool
TargetPath=\out\Release\CKAHComm.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=call tsigner "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CKAHComm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\temp\Debug\CKAHComm"
# PROP Intermediate_Dir "..\..\..\..\temp\Debug\CKAHComm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CKAHCOMM_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /I "../../../../Windows/Hook/" /I "../../../../CommonFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CKAHCOMM_EXPORTS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\..\CommonFiles" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib win32utils.lib FSDrvLib.lib rpcrt4.lib /nologo /base:"0x6A100000" /dll /pdb:"..\..\..\..\out\Debug\CKAHComm.pdb" /debug /machine:I386 /out:"..\..\..\..\out\Debug\CKAHComm.dll" /implib:"..\..\..\..\out\Debug\CKAHComm.lib" /pdbtype:sept /libpath:"../../../../CommonFiles/DebugDll" /libpath:"../../../../Out/Debug"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CKAHComm - Win32 Release"
# Name "CKAHComm - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CKAHComm.cpp
# End Source File
# Begin Source File

SOURCE=.\FltList.cpp
# End Source File
# Begin Source File

SOURCE=.\GuardClient.cpp
# End Source File
# Begin Source File

SOURCE=.\GuardFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgramExecutionLog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CKAHComm.h
# End Source File
# Begin Source File

SOURCE=.\defs.h
# End Source File
# Begin Source File

SOURCE=.\FltList.h
# End Source File
# Begin Source File

SOURCE=.\GuardClient.h
# End Source File
# Begin Source File

SOURCE=.\GuardFilter.h
# End Source File
# Begin Source File

SOURCE=.\PFFilterID.h
# End Source File
# Begin Source File

SOURCE=.\ProgramExecutionLog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CKAHComm.RC
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ver_mod.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\CommonFiles\Version\ver_mod.rc2
# End Source File
# End Group
# End Target
# End Project
