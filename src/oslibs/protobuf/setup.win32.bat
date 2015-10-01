@echo off

set ocd=%cd%
cd /d %~dp0

echo ##### ��ʾ����ȡ�����ļ� #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\config.bat
if exist ..\..\..\..\..\..\..\config.bat call ..\..\..\..\..\..\..\config.bat

echo ##### ��ʾ���������� #####
set LIB_VERSION_NAME=protobuf-2.6.1
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win32

echo ##### ��ʾ����ѹ protobuf-2.6.1 #####
%DIOS_TOOLS%\7za.exe x -y %LIB_VERSION_NAME%.tar.gz
%DIOS_TOOLS%\7za.exe x -y %LIB_VERSION_NAME%.tar
del %LIB_VERSION_NAME%.tar /Q
cd %LIB_VERSION_NAME%/vsprojects

echo ##### ��ʾ����ѹͷ�ļ� #####
call extract_includes.bat

echo ##### ��ʾ������VS������� #####
devenv.com protobuf.sln /Upgrade
echo ##### ��ʾ������ protobuf-2.6.1 #####
BuildConsole.exe protobuf.sln /prj=libprotobuf /Silent /Cfg="Debug|WIN32,Release|WIN32" 
BuildConsole.exe protobuf.sln /prj=libprotoc /Silent /Cfg="Debug|WIN32,Release|WIN32" 
BuildConsole.exe protobuf.sln /prj=protoc /Silent /Cfg="Debug|WIN32,Release|WIN32" 

echo ##### ��ʾ����װ protobuf-2.6.1 #####
if not exist %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug mkdir %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug
if not exist %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release mkdir %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release
if not exist %DIOS_PREBUILT%\inc\libprotobuf mkdir %DIOS_PREBUILT%\inc\libprotobuf

copy Release\libprotobuf.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\release\libprotobuf.lib
copy Debug\libprotobuf.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\debug\libprotobuf.lib
copy Release\protoc.exe %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release\protoc.exe
copy Debug\protoc.exe %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug\protoc.exe
xcopy /y/s include\*.h %DIOS_PREBUILT%\inc\libprotobuf


rem ---------------------
rem #### cmake ����
cd /d %~dp0

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
:eof