@echo off

set ocd=%cd%
cd /d %~dp0\..

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
SET DIOS_PLATFORM=win_x64

echo ##### ��ʾ����ѹ %BOOST_NAME% #####
if not exist %BOOST_NAME%_win goto tar
goto cd
:tar
%DIOS_TOOLS%\7za.exe x -y %BOOST_NAME%.tar.bz2
%DIOS_TOOLS%\7za.exe x -y %BOOST_NAME%.tar
del %BOOST_NAME%.tar /Q
move %BOOST_NAME% %BOOST_NAME%_win64
:cd
cd %BOOST_NAME%_win64

echo ##### ��ʾ������ %BOOST_NAME% #####
copy /y ..\bjam.exe bjam.exe
copy /y ..\b2.exe b2.exe

if defined VS140COMNTOOLS (
	SET tools=msvc-14.0
)else if defined VS120COMNTOOLS (
	SET tools=msvc-12.0
) else if defined VS110COMNTOOLS (
	SET tools=msvc-11.0
) else if defined VS100COMNTOOLS (
	SET tools=msvc-10.0
)

: ���ɳ���python������о�̬��
.\bjam.exe --without-python --without-serialization --without-regex --without-graph --without-graph_parallel --without-mpi --without-test --without-signals --toolset=%tools% variant=release threading=multi runtime-link=shared link=shared address-model=64 --exec-prefix=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release --libdir=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\  --includedir=%DIOS_PREBUILT%\inc install
if %errorlevel% neq 0 goto :cmEnd

mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release
xcopy /y/s %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\boost\*.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\release\
del %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\boost\*.dll

.\bjam.exe --without-python --without-serialization --without-regex --without-graph --without-graph_parallel --without-mpi --without-test --without-signals --toolset=%tools% variant=debug threading=multi runtime-link=shared link=shared address-model=64 --exec-prefix=%DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug --libdir=%DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\  --includedir=%DIOS_PREBUILT%\inc install
if %errorlevel% neq 0 goto :cmEnd

mkdir %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug
xcopy /y/s %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\boost\*.dll %DIOS_PREBUILT%\bin\%DIOS_PLATFORM%\debug\
del %DIOS_PREBUILT%\lib\%DIOS_PLATFORM%\boost\*.dll

cd /d %~dp0\..
echo ##### ��ʾ��CMake�������� #####
setlocal enabledelayedexpansion
call :GET_PATH_NAME %cd%
set project=%PATH_NAME%

if not exist  proj.win64 md proj.win64
cd proj.win64

echo #####��ʾ����ʼ����#####
cmake -G %DIOS_GENERATOR_X64% -DDIOS_CMAKE_PLATFORM=WIN64 ..
if %errorlevel% neq 0 goto :cmEnd
cmake -G %DIOS_GENERATOR_X64% -DDIOS_CMAKE_PLATFORM=WIN64 ..
if %errorlevel% neq 0 goto :cmEnd
echo #####��ʾ����������#####

echo #####��ʾ����ʼ����#####
rem BuildConsole.exe %project%.sln /prj=ALL_BUILD /Silent  /Cfg="Debug|x64,Release|x64" 
rem if %errorlevel% neq 0 goto :cmEnd
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