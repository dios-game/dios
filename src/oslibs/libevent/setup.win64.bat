REM 注释
@echo off

set ocd=%cd%
cd /d %~dp0

echo ##### 提示：读取配置文件 #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\..\config.bat

setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win64 md proj.win64
cd proj.win64

echo #####提示：开始构建#####
cmake -G %DIOS_GENERATOR_X64% -DDIOS_CMAKE_PLATFORM=WIN64 ..
if %errorlevel% neq 0 goto :cmEnd
cmake -G %DIOS_GENERATOR_X64% -DDIOS_CMAKE_PLATFORM=WIN64 ..
if %errorlevel% neq 0 goto :cmEnd
echo #####提示：构建结束#####

echo #####提示：开始编译#####
BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|x64,Release|x64" 
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