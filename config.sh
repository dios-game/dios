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


# -------------------------------
# -- 导出所有变量到临时文件
# -------------------------------
echo $DIOS_FRAMEWORK >var_dios_framework.txt
echo $DIOS_TOOLS >var_dios_tools.txt
echo $DIOS_DEPENDENCIES >var_dios_dependencies.txt
echo $DIOS_CMAKE >var_dios_cmake.txt

chmod 777 ${DIOS_DEPENDENCIES}/inc