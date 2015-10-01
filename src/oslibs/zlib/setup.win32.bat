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
set PROJECT=zlib
set ZLIB_ZIP_NAME=zlib128
set ZLIB_NAME=zlib-1.2.8
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=win32

echo ##### ��ʾ����ѹ %ZLIB_ZIP_NAME% #####
if not exist %ZLIB_NAME% ( %DIOS_TOOLS%\bsdtar.exe -zxvf %ZLIB_ZIP_NAME%.zip
	)
cd %ZLIB_NAME%
	
echo ##### ��ʾ������ZLIB #####
if not exist proj.win32 md proj.win32
cd proj.win32
cmake ..

echo ##### ��ʾ������ %COCOS2DX_ZIP_NAME% #####
BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|WIN32,Release|WIN32" 

echo ##### ��ʾ����װ %COCOS2DX_ZIP_NAME% #####
if not exist %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug
if not exist %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release
if not exist %DIOS_PREBUILT%\inc\zlib mkdir %DIOS_PREBUILT%\inc\zlib

copy Release\*.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\
copy Debug\*.lib %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\
copy Release\*.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\Release\
copy Debug\*.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\Debug\

xcopy /y ..\*.h %DIOS_PREBUILT%\inc\zlib\
xcopy /y *.h %DIOS_PREBUILT%\inc\zlib\


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

