# Microsoft Developer Studio Project File - Name="httpscan" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=httpscan - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "httpscan.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "httpscan.mak" CFG="httpscan - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "httpscan - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "httpscan - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PPP/MailCommon/Filters/httpscan", XWWLBAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "httpscan - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../out/Release"
# PROP Intermediate_Dir "../../../../temp/Release/ppp/httpscan"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "bl_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /O1 /I "..\..\..\include" /I "..\..\..\..\prague\include" /I "..\..\..\..\..\..\windows\hook" /I "..\..\..\..\CommonFiles" /I "..\..\..\..\klava\kernel\include" /D "_PRAGUE_TRACE_" /D "NDEBUG" /D "bl_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "C_STYLE_PROP" /D "DIRECT_SEND_EVENTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /i ".\..\..\..\..\CommonFiles" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib advapi32.lib klaveng.lib /nologo /base:"0x64200000" /dll /debug /machine:I386 /out:"../../../../out/Release/httpscan.ppl" /libpath:"../lib/release" /libpath:"..\..\CommonFiles\ReleaseDll" /libpath:"../../../../out/release" /opt:ref
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=\out\Release\httpscan.ppl
SOURCE="$(InputPath)"
PostBuild_Desc=Postbuild...
PostBuild_Cmds=tsigner "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "httpscan - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../out/Debug"
# PROP Intermediate_Dir "../../../../temp/Debug/ppp/httpscan"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "bl_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\..\prague\include" /I "..\..\..\..\..\..\windows\hook" /I "..\..\..\..\CommonFiles" /I "..\..\..\..\klava\kernel\include" /D "_DEBUG" /D "_PRAGUE_TRACE_" /D "httpscan_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "C_STYLE_PROP" /D "DIRECT_SEND_EVENTS" /FD /GZ /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /i ".\..\..\..\..\CommonFiles" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib advapi32.lib klaveng.lib /nologo /dll /debug /machine:I386 /out:"../../../../out/Debug/httpscan.ppl" /pdbtype:sept /libpath:"../lib/Debug" /libpath:"../../CommonFiles/DebugDll" /libpath:"../../../../out/debug"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "httpscan - Win32 Release"
# Name "httpscan - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\plugin_httpscan.cpp
# End Source File
# Begin Source File

SOURCE=.\streamingprocessor.cpp
# End Source File
# Begin Source File

SOURCE=.\task.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\Include\plugin\p_httpscan.h
# End Source File
# Begin Source File

SOURCE=.\streamingprocessor.h
# End Source File
# Begin Source File

SOURCE=.\ver_mod.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\httpscan.imp
# End Source File
# Begin Source File

SOURCE=.\httpscan.meta
# End Source File
# Begin Source File

SOURCE=.\httpscan.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "ThreadImp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\ThreadImp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ThreadImp.h
# End Source File
# End Group
# Begin Group "gzipstm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gzipstm\gzipstm.c
# End Source File
# Begin Source File

SOURCE=.\gzipstm\gzipstm.h
# End Source File
# End Group
# End Target
# End Project
