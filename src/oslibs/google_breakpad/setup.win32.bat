@echo off

set ocd=%cd%
cd /d %~dp0

echo ##### 提示：读取配置文件 #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat

echo ##### 提示：变量配置 #####
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win32
set LIBRARY_DIRECTORY_DEBUG=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug
set LIBRARY_DIRECTORY_RELEASE=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release
set INCLUDE_DIRECTORY=%DIOS_PREBUILT%\inc\google_breakpad

cd google-breakpad-read-only

mkdir %LIBRARY_DIRECTORY_DEBUG%
mkdir %LIBRARY_DIRECTORY_RELEASE%
mkdir %INCLUDE_DIRECTORY%

cd src\client\windows
call ..\..\tools\gyp\gyp.bat --no-circular-check breakpad_client.gyp

cd ..\..\..\

call %tools%vsvars32.bat
:BuildConsole.exe src\client\windows\breakpad_client.sln /prj=exception_handler  /Cfg="Debug|WIN32,Release|WIN32" 
:BuildConsole.exe src\client\windows\breakpad_client.sln /prj=crash_generation_client  /Cfg="Debug|WIN32,Release|WIN32" 
:BuildConsole.exe src\client\windows\breakpad_client.sln /prj=common  /Cfg="Debug|WIN32,Release|WIN32" 

: load_vsvars
: using devenv directly - buildconsole doesn't support building vs2010 vcxproj files directly, yet
devenv.com src\client\windows\breakpad_client.sln /Upgrade
devenv.com src\client\windows\breakpad_client.sln /build "release" /project exception_handler
devenv.com src\client\windows\breakpad_client.sln /build "debug" /project exception_handler
devenv.com src\client\windows\breakpad_client.sln /build "release" /project crash_generation_client
devenv.com src\client\windows\breakpad_client.sln /build "debug"  /project crash_generation_client
devenv.com src\client\windows\breakpad_client.sln /build "release"  /project common
devenv.com src\client\windows\breakpad_client.sln /build "debug"  /project common
: devenv.com src\tools\windows\dump_syms\dump_syms.vcproj /Upgrade
: devenv.com src\tools\windows\dump_syms\dump_syms.vcxproj /build "release|win32" 

mkdir %INCLUDE_DIRECTORY%"\client\windows\common"
mkdir %INCLUDE_DIRECTORY%"\client\windows\crash_generation"
mkdir %INCLUDE_DIRECTORY%"\common\windows"
mkdir %INCLUDE_DIRECTORY%"\google_breakpad\common"
mkdir %INCLUDE_DIRECTORY%"\processor"

copy /Y .\src\client\windows\handler\exception_handler.h "%INCLUDE_DIRECTORY%"
copy /Y src\client\windows\common\*.h "%INCLUDE_DIRECTORY%\client\windows\common"
copy /Y src\common\windows\*.h "%INCLUDE_DIRECTORY%\common\windows"
copy /Y src\client\windows\crash_generation\*.h "%INCLUDE_DIRECTORY%\client\windows\crash_generation"
copy /Y src\google_breakpad\common\*.h "%INCLUDE_DIRECTORY%\google_breakpad\common"
copy /Y src\common\*.h "%INCLUDE_DIRECTORY%\common"
copy /Y src\processor\scoped_ptr.h "%INCLUDE_DIRECTORY%\processor"
copy /Y .\src\client\windows\Debug\lib\*.lib "%LIBRARY_DIRECTORY_DEBUG%"
copy /Y .\src\client\windows\Release\lib\*.lib "%LIBRARY_DIRECTORY_RELEASE%"

mkdir %DIOS_PREBUILT%\LICENSES
copy /Y COPYING %DIOS_PREBUILT%\LICENSES\google_breakpad.txt

cd /d %~dp0

setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win32 md proj.win32
cd proj.win32

echo #####提示：开始构建#####
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
if %errorlevel% neq 0 goto :cmEnd
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
if %errorlevel% neq 0 goto :cmEnd
echo #####提示：构建结束#####

echo #####提示：开始编译#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent /OpenMonitor /Cfg="Debug|WIN32,Release|WIN32" 
BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 
if %errorlevel% neq 0 goto :cmEnd
echo #####提示：编译结束#####

echo #####提示：开始安装#####
cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
echo #####提示：安装结束#####

goto cmDone
:cmEnd
echo setup failed
pause
exit

:cmDone
cmake -P dios_cmake_compile_succeeded.cmake
cmake -P dios_cmake_install_succeeded.cmake
cd /d %ocd%
@echo on

goto :eof
:GET_PATH_NAME
set PATH_NAME=%~n1
:eof