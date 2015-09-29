@echo off

set ocd=%cd%
cd /d %~dp0

echo ##### ������?��o?����????????t #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\..\config.bat

echo ##### ������?��o��?��????? #####
set LIBCURL_VERSION_NAME=curl-7.33.0
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win_x86
set BIN_DIRECTORY_DEBUG=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug
set BIN_DIRECTORY_RELEASE=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release
set LIBRARY_DIRECTORY_DEBUG=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug
set LIBRARY_DIRECTORY_RELEASE=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release
set INCLUDE_DIRECTORY=%DIOS_PREBUILT%\inc\libcurl

echo ##### ������?��o?a?1 %LIBCURL_VERSION_NAME% #####
if not exist %LIBCURL_VERSION_NAME% (
	rem ?a?12������
	%DIOS_TOOLS%\7za.exe x -y %LIBCURL_VERSION_NAME%.tar.bz2
	%DIOS_TOOLS%\7za.exe x -y %LIBCURL_VERSION_NAME%.tar
	del %LIBCURL_VERSION_NAME%.tar /Q
	)

cd %LIBCURL_VERSION_NAME%

mkdir %BIN_DIRECTORY_DEBUG%
mkdir %BIN_DIRECTORY_RELEASE%
mkdir %LIBRARY_DIRECTORY_DEBUG%
mkdir %LIBRARY_DIRECTORY_RELEASE%
mkdir %INCLUDE_DIRECTORY%

echo ##### ������?��oVC?��?3 #####
mkdir vc
cd vc
cmake ..

echo ##### ������?��o������? #####
BuildConsole.exe CURL.sln /prj=libcurl /Silent /Cfg="Debug|WIN32,Release|WIN32" 

echo ##### ������?��o??���� #####
copy /y ..\include\curl\*.h %INCLUDE_DIRECTORY%
copy /y lib\Debug\*.dll %BIN_DIRECTORY_DEBUG%
copy /y lib\Release\*.dll %BIN_DIRECTORY_RELEASE%
copy /Y lib\Debug\*.lib "%LIBRARY_DIRECTORY_DEBUG%"
copy /Y lib\Release\*.lib "%LIBRARY_DIRECTORY_RELEASE%"

rem ### cmake ?��1?
cd /d %~dp0
setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win32 md proj.win32
cd proj.win32

echo #####������?��o?a��?11?��#####
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
echo %errorlevel%
if %errorlevel% neq 0 goto :cmEnd
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
echo %errorlevel%
if %errorlevel% neq 0 goto :cmEnd
echo #####������?��o11?��?����?#####

echo #####������?��o?a��?������?#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent /OpenMonitor /Cfg="Debug|WIN32,Release|WIN32" 
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 
rem if %errorlevel% neq 0 goto :cmEnd
echo #####������?��o������??����?#####

echo #####������?��o?a��?��2����#####
cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
echo #####������?��o��2����?����?#####

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