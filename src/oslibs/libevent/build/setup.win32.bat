REM 注释
@echo off

set ocd=%cd%
cd /d %~dp0
cd ..

echo ##### 提示：读取配置文件 #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\..\config.bat

echo ##### 提示：变量配置 #####
set LIBEVENT_VERSION_NAME=libevent-2.0.21-stable
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win_x86

echo ##### 提示：解压 %LIBEVENT_VERSION_NAME% #####
if not exist %LIBEVENT_VERSION_NAME% (
	
	rem 解压操作
	%DIOS_TOOLS%\7za.exe x -y %LIBEVENT_VERSION_NAME%.tar.gz
	%DIOS_TOOLS%\7za.exe x -y %LIBEVENT_VERSION_NAME%.tar
	del %LIBEVENT_VERSION_NAME%.tar /Q
	
	rem 代码补丁
	xcopy /y /s patch\* %LIBEVENT_VERSION_NAME%\
	)

echo ##### 提示：编译 LibEvent #####	
cd %LIBEVENT_VERSION_NAME%

echo ##### 提示：编译 %LIBEVENT_VERSION_NAME% #####
nmake makefile.nmake
if %errorlevel% neq 0 goto :cmEnd

echo ##### 提示：安装 libevent #####

if not exist %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\libevent mkdir %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%
if not exist %DIOS_PREBUILT%\inc\libevent mkdir %DIOS_PREBUILT%\inc\libevent
if not exist %DIOS_PREBUILT%\inc\libevent\WIN32-Code mkdir %DIOS_PREBUILT%\inc\libevent\WIN32-Code

copy libevent.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\
copy libevent_core.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\
copy libevent_extras.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\

xcopy /y/s include\*.h %DIOS_PREBUILT%\inc\libevent
xcopy /y/s WIN32-Code\*.h %DIOS_PREBUILT%\inc\libevent

rem ---------------------


rem #### cmake 编译

cd /d %~dp0
cd ..

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
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 
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