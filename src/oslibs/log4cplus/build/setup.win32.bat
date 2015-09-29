REM ע��
@echo off

set ocd=%cd%
cd /d %~dp0
cd ..

echo ##### ��ʾ����ȡ�����ļ� #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\..\config.bat

echo ##### ��ʾ���������� #####
set LIB_VERSION_NAME=log4cplus-1.1.3-rc1
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win_x86
set BIN_DIRECTORY_DEBUG=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug
set BIN_DIRECTORY_RELEASE=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release
set LIBRARY_DIRECTORY_DEBUG=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%
set LIBRARY_DIRECTORY_RELEASE=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%
set INCLUDE_DIRECTORY=%DIOS_PREBUILT%\inc\log4cplus

echo ##### ��ʾ����ѹ %LIB_VERSION_NAME% #####
if not exist %LIB_VERSION_NAME% (
	rem ��ѹ����
	%DIOS_TOOLS%\7za.exe x -y %LIB_VERSION_NAME%.tar.bz2
	%DIOS_TOOLS%\7za.exe x -y %LIB_VERSION_NAME%.tar
	del %LIB_VERSION_NAME%.tar /Q
	)
	
xcopy /y /s patch\* %LIB_VERSION_NAME%\
cd %LIB_VERSION_NAME%

mkdir %BIN_DIRECTORY_DEBUG%
mkdir %BIN_DIRECTORY_RELEASE%
mkdir %LIBRARY_DIRECTORY_DEBUG%
mkdir %LIBRARY_DIRECTORY_RELEASE%
mkdir %INCLUDE_DIRECTORY%

echo ##### ��ʾ��VC���� #####
mkdir vc
cd vc
cmake ..

echo ##### ��ʾ������ #####
BuildConsole.exe log4cplus.sln /prj=log4cplus /Silent /Cfg="Debug|WIN32,Release|WIN32" 
echo ##### ��ʾ������ #####
xcopy /y /s include\log4cplus\* %INCLUDE_DIRECTORY%
xcopy /y /s ..\include\log4cplus\* %INCLUDE_DIRECTORY%
xcopy /y /s bin\Debug\*.dll %BIN_DIRECTORY_DEBUG%
xcopy /y /s bin\Release\*.dll %BIN_DIRECTORY_RELEASE%
xcopy /y /s src\Debug\*.lib "%LIBRARY_DIRECTORY_DEBUG%"
xcopy /y /s src\Release\*.lib "%LIBRARY_DIRECTORY_RELEASE%"

rem ### cmake ���
cd /d %~dp0
cd ..
setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win32 md proj.win32
cd proj.win32

echo #####��ʾ����ʼ����#####
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
if %errorlevel% neq 0 goto :cmEnd
cmake -DDIOS_CMAKE_PLATFORM=WIN32 ..
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ����������#####

echo #####��ʾ����ʼ����#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent /OpenMonitor /Cfg="Debug|WIN32,Release|WIN32" 
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ���������#####

echo #####��ʾ����ʼ��װ#####
cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ����װ����#####

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