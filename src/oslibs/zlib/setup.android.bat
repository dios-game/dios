@echo off

set ocd=%cd%
set ZLIB_ZIP_NAME=zlib128
set ZLIB_NAME=zlib-1.2.8

set project=zlib
cd /d %~dp0

echo ##### ��ʾ����ȡ�����ļ� #####
if exist ..\config.bat call ..\config.bat
if exist ..\..\config.bat call ..\..\config.bat
if exist ..\..\..\config.bat call ..\..\..\config.bat
if exist ..\..\..\..\config.bat call ..\..\..\..\config.bat
if exist ..\..\..\..\..\config.bat call ..\..\..\..\..\config.bat

echo ##### ��ʾ����ѹ %ZLIB_ZIP_NAME% #####
if not exist %ZLIB_NAME% ( %DXM_TOOLS%\win\bsdtar.exe -zxvf %ZLIB_ZIP_NAME%.zip
	)
	
echo ##### ��ʾ���򲹶� #####
rem xcopy /y/s patch\* %COCOS2DX_ZIP_NAME%\

md proj.android\jni
copy /y Android.mk proj.android\jni

cd %ocd%
@echo on

