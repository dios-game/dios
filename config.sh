#! /bin/bash

# -------------------------------
# -- DIOS 变量
# -------------------------------
export DIOS_PROJECT_PATH=$(cd $(dirname $BASH_SOURCE); pwd)
export DIOS_PATH=${DIOS_PROJECT_PATH}/dios
export DIOS_COCOS_PATH=${DIOS_PROJECT_PATH}/src/oslibs/cocos/cocos-src

# -------------------------------
# -- DIOS 变量
# -------------------------------
export DIOS_INSTALL=${DIOS_PROJECT_PATH}/install
export DIOS_TOOLS=${DIOS_PATH}/build/tools
export DIOS_CMAKE=${DIOS_PATH}/build/cmake
