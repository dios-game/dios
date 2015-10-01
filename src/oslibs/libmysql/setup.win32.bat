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

echo ##### 提示：变量配置 #####
SET mysql_name=mysql-connector-c-6.1.6-src
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win32

echo ##### 提示：解压 %mysql_name% #####
IF EXIST %mysql_name%-win GOTO FILE_EXISTED
%DIOS_TOOLS%\7za.exe x -y %mysql_name%.tar.gz
%DIOS_TOOLS%\7za.exe x -y %mysql_name%.tar
del %mysql_name%.tar /Q

move /y %mysql_name% %mysql_name%-win

: FILE_EXISTED
cd %mysql_name%-win

echo ##### 提示：构建 %mysql_name% #####
cmake .

echo ##### 提示：编译 %mysql_name% #####
BuildConsole.exe libmysql.sln /prj=libmysql /Silent /Cfg="Debug|WIN32,Release|WIN32"

echo ##### 提示：安装 %mysql_name% #####
REM 创建文件夹
if not exist %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\libmysql\debug mkdir %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug
if not exist %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\libmysql\release mkdir %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release
if not exist %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug
if not exist %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release
IF not exist %DIOS_PREBUILT%\inc\libmysql mkdir %DIOS_PREBUILT%\inc\libmysql
REM 拷贝文件到安装目录
copy libmysql\Debug\libmysql.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug\libmysql.lib
REM copy libmysql\Debug\mysqlclient.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug\mysqlclient.lib
copy libmysql\Release\libmysql.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release\libmysql.lib
REM copy libmysql\Release\mysqlclient.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release\mysqlclient.lib
copy libmysql\Debug\libmysql.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug\libmysql.dll
copy libmysql\Release\libmysql.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release\libmysql.dll
xcopy /y/s include\*.* %DIOS_PREBUILT%\inc\libmysql

rem ### CMAKE
cd /d %~dp0

setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win32 md proj.win32
cd proj.win32

echo #####提示：开始构建#####
cmake -Ddios_CMAKE_PLATFORM=WIN32 ..
echo %errorlevel%
if %errorlevel% neq 0 goto :cmEnd
cmake -Ddios_CMAKE_PLATFORM=WIN32 ..
echo %errorlevel%
if %errorlevel% neq 0 goto :cmEnd
echo #####提示：构建结束#####

echo #####提示：开始编译#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent /OpenMonitor /Cfg="Debug|WIN32,Release|WIN32" 
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 
rem if %errorlevel% neq 0 goto :cmEnd
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

goto :eof
:GET_PATH_NAME
set PATH_NAME=%~n1
:eof
