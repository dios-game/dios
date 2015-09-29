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
SET BOOST_NAME=boost_1_55_0
SET DIOS_PREBUILT=%cd%\prebuilt
SET DIOS_PLATFORM=android

echo ##### ��ʾ����ѹ %BOOST_NAME% #####
if not exist %BOOST_NAME%_android goto tar
goto patch
:tar
%DIOS_TOOLS%\7za.exe x -y %BOOST_NAME%.tar.bz2
%DIOS_TOOLS%\7za.exe x -y %BOOST_NAME%.tar
del %BOOST_NAME%.tar /Q
move %BOOST_NAME% %BOOST_NAME%_android

:patch
echo ##### ��ʾ������ %BOOST_NAME% #####
%DIOS_TOOLS%\patch -Np1 -d %BOOST_NAME%_android < patch\android\windows\%BOOST_NAME%.patch
copy /y patch\android\user-config.jam %BOOST_NAME%_android\tools\build\v2\

:cd
cd %BOOST_NAME%_android
rmdir /S /Q bin.v2

echo ##### ��ʾ������ %BOOST_NAME% #####
copy /y ..\bjam.exe bjam.exe
copy /y ..\b2.exe b2.exe

bjam --toolset=gcc-androidR10e threadapi=pthread target-os=linux --with-chrono --with-date_time --with-signals --with-system --with-thread link=static runtime-link=static threading=multi --exec-prefix=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM% --libdir=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM% --includedir=%DIOS_PREBUILT%\inc install
if %errorlevel% neq 0 goto :cmEnd
cd ..

md proj.android\jni
copy /y Android.mk proj.android\jni

rem ##### cmake����
cd proj.android

echo #####��ʾ����ʼ����#####
cmake -DDIOS_CMAKE_PLATFORM=ANDROID -P ..\CMakeListsAndroid.cmake
rem cmake -DDIOS_CMAKE_PLATFORM=ANDROID -P ..\CMakeListsAndroid.cmake
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ����������#####

echo #####��ʾ����ʼ����#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD  /Cfg="Debug|WIN32,Release|WIN32" 
rem call build.bat
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ���������#####

echo #####��ʾ����ʼ��װ#####
rem cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
rem cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
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

