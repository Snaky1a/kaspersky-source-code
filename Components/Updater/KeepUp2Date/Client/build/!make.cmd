echo off

date /t >> timing.txt
time /t >> timing.txt
echo.   >> timing.txt

rem *** some basic checking
if "%1" == "" goto label_usage
if "%kl_buildno%" == "" goto label_emptybld

rem *** internal variables
set prod_name=Updater_for_SCM4Exchange
set base_path=O:
rem set prod_path=%base_path%\windows\workstation5.0\ak_plugin
rem set target_path=D:\%prod_name%.1.0.0.%kl_buildno%
rem set is_proj_dir=%target_path%\KAVWst50ConsolePlugin
rem set isprj_name=KAVWst50ConsolePlugin.isv
set testing=\\kl\global\testing\kav50\UpdaterSCM4Exchange
set testing_prod=%testing%\1.0.0.%kl_buildno%

echo Making 1.0.0.%kl_buildno% version of %prod_name%...

echo Arguments parsing...
:analyze
if "%1" == "" goto begin
if /i "%1" EQU "-setlbl" set setlbl=1
if /i "%1" EQU "-get" set get=1
if /i "%1" EQU "-build_all" set build_debug=1 & set build_release=1
if /i "%1" EQU "-build_debug" set build_debug=1
if /i "%1" EQU "-build_release" set build_release=1
if /i "%1" EQU "-clean" set clean_build=1
if /i "%1" EQU "-copy_tst" set copy_tst=1
shift
goto analyze

:begin
rem *** at least one key option must be set
if "%setlbl%%get%%build_all%%build_debug%%build_release%%copy_tst%" == "" goto label_nokeyopt

:label_set_labels
if not defined setlbl goto label_get_files

echo Setting labels on projects from SourceSafe...
start /min /wait cmd /q /c ".\setlabels.cmd 2> .\setlabelserrors.log"
if not %errorlevel% == 0 goto label_error

:label_get_files
if not defined get goto label_make_version

echo Getting files from SourceSafe...
start /min /wait cmd /q /c ".\getfiles.cmd %base_path% 2> .\getfileserrors.log"
if not %errorlevel% == 0 goto label_error

:label_make_version
if not defined build_debug if not defined build_release goto label_build_debug

echo Creating version info file...
call setversion.cmd %base_path%
if not %errorlevel% == 0 goto label_error

:label_build_debug
if not defined build_debug goto label_build_release

echo Building project files (debug version)...
if defined clean_build call .\modules_debug.cmd .\build_modules_debug.log /CLEAN /REBUILD
if not defined clean_build call .\modules_debug.cmd .\build_modules_debug.log
if not %errorlevel% == 0 goto label_error
echo Build (debug) finished successfully.

:label_build_release
if not defined build_release goto label_build_end

echo Building project files (release version)...
if defined clean_build call .\modules_release.cmd .\build_modules_release.log /CLEAN /REBUILD
if not defined clean_build call .\modules_release.cmd .\build_modules_release.log
if not %errorlevel% == 0 goto label_error
echo Build (release) finished successfully.

:label_build_end
if not defined copy_tst goto label_end

echo Copying source files...
xcopy /s /q /c /r /y /exclude:excludes.lst %base_path%\Components\* %testing_prod%\Source\Components\
xcopy /s /q /c /r /y /exclude:excludes.lst %base_path%\CommonFiles\* %testing_prod%\Source\CommonFiles\

echo Copying files to testing...
xcopy /s /q /c /r /y %base_path%\Components\KeepUp2Date\Client\IUpdater\bin.release\IUpdater.exe %testing_prod%\Release\
xcopy /s /q /c /r /y %base_path%\Components\KeepUp2Date\Client\IUpdater\bin.release\IUpdater.pdb %testing_prod%\Release\

xcopy /s /q /c /r /y %base_path%\Components\KeepUp2Date\Client\IUpdater\bin.debug\IUpdater.exe %testing_prod%\Debug\
xcopy /s /q /c /r /y %base_path%\Components\KeepUp2Date\Client\IUpdater\bin.debug\IUpdater.pdb %testing_prod%\Debug\

echo Copying finished successfully.

goto label_end

:label_nokeyopt
echo At least one key option must be set
echo.

:label_usage
echo "Usage: make.cmd <options>"
echo ^	-setlbl:	set labels on projects from SourceSafe
echo ^	-get:		get files from SourceSafe
echo ^	-build_all:	build product modules (both release and debug versions)
echo ^	-build_debug:	build product modules (only debug version)
echo ^	-build_release:	build product modules (only release version)
echo ^	-clean:		clean before build
echo ^	-copy_tst:	copy files to testing
goto label_end

:label_emptybld
echo Environment variable "kl_buildno" is not set
goto label_end

:label_error
echo Build failed.
goto label_end

:label_warning
echo Warning... 
goto label_end

:label_end

date /t >> timing.txt
time /t >> timing.txt
echo.   >> timing.txt

exit