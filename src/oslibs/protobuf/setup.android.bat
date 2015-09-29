@echo off

set ocd=%cd%
set PROTOBUF_ZIP_NAME=protobuf-2.6.1
cd /d %~dp0

echo ##### 提示：读取配置文件 #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat

echo ##### 提示：解压 %PROTOBUF_ZIP_NAME% #####
if not exist %PROTOBUF_ZIP_NAME% (%DXM_TOOLS%\win\7za.exe x -y %PROTOBUF_ZIP_NAME%.tar.gz
%DXM_TOOLS%\win\7za.exe x -y %PROTOBUF_ZIP_NAME%.tar
del %PROTOBUF_ZIP_NAME%.tar /Q
)

md proj.android\jni
copy /y Android.mk proj.android\jni

cd %ocd%
@echo on

