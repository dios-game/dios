@echo off

echo export resources to assets folder
copy ..\..\resources assets

echo encrypt lua
del /s/q assets\src\*
cocos luacompile -s ../../resources/src -d assets/src/ -e -k num24 -b dios-mao
