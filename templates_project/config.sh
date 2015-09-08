#! /bin/bash

# -- 用户手动配置

# -------------------------------
# -- IOS
# -------------------------------

# -------------------------------
# -- Tools
# -------------------------------

# -- 系统自动配置

# -------------------------------
# -- IOS
# -------------------------------

# -------------------------------
# -- DIOS
# -------------------------------
DIOS_FRAMEWORK=$(pwd)/$(dirname $0)
DIOS_TOOLS=${DIOS_FRAMEWORK}/dios/tools
DIOS_INSTALL=${DIOS_FRAMEWORK}/install
DIOS_CMAKE=${DIOS_FRAMEWORK}/dios/cmake

# -- 导出所有变量到临时文件
echo $DIOS_FRAMEWORK >var_dios_framework.txt
echo $DIOS_TOOLS >var_dios_tools.txt
echo $DIOS_INSTALL >var_dios_install.txt
echo $DIOS_CMAKE >var_dios_cmake.txt

chmod 777 ${DIOS_INSTALL}/inc