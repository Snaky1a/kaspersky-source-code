# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PPP/MailCommon/Interceptors/TrafficMonitor2/ProtocollersEx/test", QUKHBAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../../../CSShare" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../../../out/Debug"
# PROP Intermediate_Dir "../../../../../../temp/Debug/test"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /I "../../.." /I "../../../../../../../CommonFiles" /I "../../../../../../../prague/include" /I "../../../../../../../ppp/include" /I "../../../../../../../ppp/CSShare" /I "../../../../../../../prague" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "BOOST_SPIRIT_THREADSAFE" /D "BOOST_THREAD_CONFIG_WEK01032003_HPP" /D BOOST_THREAD_DECL="" /FD /GZ /Zm1000 /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib advapi32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\http\analyzerimpl.cpp
# End Source File
# Begin Source File

SOURCE=.\auxfunc.cpp
# End Source File
# Begin Source File

SOURCE=..\common\BaseProtocolAnalyzerImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\cached_strategy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\CSShare\libs\thread\src\exceptions.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\generic_strategy.cpp
# End Source File
# Begin Source File

SOURCE=.\http_test_cases.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\http_utils.cpp
# End Source File
# Begin Source File

SOURCE=..\imap\ImapMessageDataParser.cpp
# End Source File
# Begin Source File

SOURCE=..\imap\ImapProtocolAnalyzerImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\imap\ImapUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\http\message.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\message_builder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\CSShare\libs\thread\src\mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\nntp\NntpProtocolAnalyzerImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\CSShare\libs\thread\src\once.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\processor.cpp
# End Source File
# Begin Source File

SOURCE=..\http\recognizer.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\service_proxy.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\session.cpp
# End Source File
# Begin Source File

SOURCE=..\http\skip_app.cpp
# End Source File
# Begin Source File

SOURCE=..\common\SplitTextBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\HTTPProtocoller\stream_strategy.cpp
# End Source File
# Begin Source File

SOURCE=..\http\takeurl.cpp
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\CSShare\libs\thread\src\tss.cpp
# End Source File
# Begin Source File

SOURCE=..\http\verifyssl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\CSShare\libs\thread\src\xtime.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\http\analyzerimpl.h
# End Source File
# Begin Source File

SOURCE=.\auxfunc.h
# End Source File
# Begin Source File

SOURCE=..\common\BaseProtocolAnalyzerImpl.h
# End Source File
# Begin Source File

SOURCE=..\common\ContentItem.h
# End Source File
# Begin Source File

SOURCE=..\common\DataBuffer.h
# End Source File
# Begin Source File

SOURCE=..\extra\DefaultContentHandler.h
# End Source File
# Begin Source File

SOURCE=.\http_test_cases.h
# End Source File
# Begin Source File

SOURCE=..\extra\IContentHandler.h
# End Source File
# Begin Source File

SOURCE=..\imap\ImapMessageDataParser.h
# End Source File
# Begin Source File

SOURCE=..\imap\ImapProtocolAnalyzerImpl.h
# End Source File
# Begin Source File

SOURCE=..\imap\ImapUtil.h
# End Source File
# Begin Source File

SOURCE=..\interfaces\IProtocolAnalyzer.h
# End Source File
# Begin Source File

SOURCE=..\common\IProtocolAnalyzerEx.h
# End Source File
# Begin Source File

SOURCE=..\extra\ISessionProxy.h
# End Source File
# Begin Source File

SOURCE=..\http\message.h
# End Source File
# Begin Source File

SOURCE=..\http\message.hpp
# End Source File
# Begin Source File

SOURCE=..\nntp\NntpProtocolAnalyzer.h
# End Source File
# Begin Source File

SOURCE=..\nntp\NntpProtocolAnalyzerImpl.h
# End Source File
# Begin Source File

SOURCE=..\common\ProtocolAnalyzerImplAdapter.h
# End Source File
# Begin Source File

SOURCE=..\extra\ProtocolProcessingManager.h
# End Source File
# Begin Source File

SOURCE=..\extra\ProtocolProcessor.h
# End Source File
# Begin Source File

SOURCE=..\common\SplitTextBuffer.h
# End Source File
# Begin Source File

SOURCE=..\common\StringUtil.h
# End Source File
# Begin Source File

SOURCE=..\interfaces\TrafficProtocollerTypes.h
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
