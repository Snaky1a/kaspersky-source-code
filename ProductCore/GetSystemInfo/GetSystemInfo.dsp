# Microsoft Developer Studio Project File - Name="GetSystemInfo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GetSystemInfo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GetSystemInfo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GetSystemInfo.mak" CFG="GetSystemInfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GetSystemInfo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GetSystemInfo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PPP/GetSystemInfo", NDUGBAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GetSystemInfo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\out\release"
# PROP Intermediate_Dir "..\..\temp\release\ppp\getsysteminfo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GETSYSTEMINFO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GETSYSTEMINFO_EXPORTS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib msvcrt.lib /nologo /base:"0x63d00000" /dll /debug /machine:I386 /opt:ref /EXPORT:SaveReport
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=\out\release\GetSystemInfo.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=tsigner "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GetSystemInfo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\out\debug"
# PROP Intermediate_Dir "..\..\temp\debug\ppp\getsysteminfo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GETSYSTEMINFO_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GETSYSTEMINFO_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /pdbtype:sept /EXPORT:SaveReport
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GetSystemInfo - Win32 Release"
# Name "GetSystemInfo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdditionPrinter.cpp
# End Source File
# Begin Source File

SOURCE=.\AssociateString.cpp
# End Source File
# Begin Source File

SOURCE=.\FileVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\GetSystemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GetSystemInfoMain.cpp
# End Source File
# Begin Source File

SOURCE=.\HardDriveWork.cpp
# End Source File
# Begin Source File

SOURCE=.\HardWareInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryScan.cpp
# End Source File
# Begin Source File

SOURCE=.\SoftWareInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\StartUpLinks.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AdditionPrinter.h
# End Source File
# Begin Source File

SOURCE=.\AssociatedString.h
# End Source File
# Begin Source File

SOURCE=.\FileVersion.h
# End Source File
# Begin Source File

SOURCE=.\GetSystemInfo.h
# End Source File
# Begin Source File

SOURCE=.\GetSystemInfoMain.h
# End Source File
# Begin Source File

SOURCE=.\HardDriveWork.h
# End Source File
# Begin Source File

SOURCE=.\HardWareInfo.h
# End Source File
# Begin Source File

SOURCE=.\MemoryScan.h
# End Source File
# Begin Source File

SOURCE=.\PORT32.H
# End Source File
# Begin Source File

SOURCE=.\PSAPI.H
# End Source File
# Begin Source File

SOURCE=.\SoftWareInfo.h
# End Source File
# Begin Source File

SOURCE=.\StartUpLinks.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubDefines.h
# End Source File
# Begin Source File

SOURCE=.\SysInfoDefines.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
