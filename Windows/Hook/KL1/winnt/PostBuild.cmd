@echo off

echo hello %USERNAME% !

if %USERNAME%== Foxgen goto _FoxGen
if %USERNAME%== Sobko goto _Sobko

goto _after_private

rem ----------------------------------------------------------------
rem This section only for FoxGen
:_FoxGen
goto :_after_private

:_FoxGen_Post
echo PostBuildStep ---- copy symbols to symserver
goto _Finish
rem End of _FoxGen section
rem ----------------------------------------------------------------

rem ----------------------------------------------------------------
rem This section only for Sobko
:_Sobko
goto :_after_private

:_Sobko_Post
echo PostBuildStep ---- copy symbols to symserver
goto _Finish
rem End of _Sobko section
rem ----------------------------------------------------------------


:_after_private


if %1 == Release goto _Release
if %1 == Debug goto _Debug
if %1 == kl1_nt___Win32_XP_Debug goto _kl1_nt___Win32_XP_Debug
if %1 == kl1_nt___Win32_XP_Release goto _kl1_nt___Win32_XP_Release

echo PostBuildStep ---- ERROR!!! - nor Release nor Debug

goto _Exit

:_Release
echo PostBuildStep ---- Release detected
copy .\Release\kl1.sys ..\..\Release\kl1.sys
copy .\Release\kl1.pdb ..\..\Release\kl1.pdb
goto _Exit

:_Debug
echo PostBuildStep ---- Debug detected
copy .\Debug\kl1.sys ..\..\Debug\kl1.sys
copy .\Debug\kl1.pdb ..\..\Debug\kl1.pdb
goto _Exit

:_kl1_nt___Win32_XP_Debug
echo PostBuildStep ---- XP Debug detected
goto _Exit

:_kl1_nt___Win32_XP_Release
echo PostBuildStep ---- XP Release detected
goto _Exit


:_Exit
if %USERNAME%== Foxgen goto _FoxGen_Post
if %USERNAME%== Sobko goto _Sobko_Post

:_Finish
echo PostBuildStep ---- Finished
