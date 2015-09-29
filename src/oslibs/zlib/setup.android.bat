@echo off

set ocd=%cd%
set ZLIB_ZIP_NAME=zlib128
set ZLIB_NAME=zlib-1.2.8

set project=zlib
cd /d %~dp0

echo ##### 提示：读取配置文件 #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat

echo ##### 提示：解压 %ZLIB_ZIP_NAME% #####
if not exist %ZLIB_NAME% ( %DXM_TOOLS%\win\bsdtar.exe -zxvf %ZLIB_ZIP_NAME%.zip
	)
	
echo ##### 提示：打补丁 #####
rem xcopy /y/s patch\* %COCOS2DX_ZIP_NAME%\

md proj.android\jni
copy /y Android.mk proj.android\jni

cd %ocd%
@echo on

