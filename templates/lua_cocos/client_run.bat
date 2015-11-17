@echo off

set ocd=%cd%
cd /d %~dp0

cd resources
call ..\runtime\bin\win32\num24.exe 