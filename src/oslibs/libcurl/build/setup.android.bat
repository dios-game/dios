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

setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.android md proj.android
cd proj.android

echo #####��ʾ����ʼ����#####
cmake -GNinja -DDIOS_CMAKE_PLATFORM=ANDROID -DCMAKE_TOOLCHAIN_FILE=%dios_CMAKE%\toolchain\android\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi" -DANDROID_STL=gnustl_shared ..
if %errorlevel% neq 0 goto :cmEnd
cmake -GNinja -DDIOS_CMAKE_PLATFORM=ANDROID -DCMAKE_TOOLCHAIN_FILE=%dios_CMAKE%\toolchain\android\android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi" -DANDROID_STL=gnustl_shared ..
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ����������#####

echo #####��ʾ����ʼ����#####
rem cmake --build .
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ���������#####

echo #####��ʾ����ʼ��װ#####
rem cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
rem if %errorlevel% neq 0 goto :cmEnd
rem cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
rem if %errorlevel% neq 0 goto :cmEnd
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