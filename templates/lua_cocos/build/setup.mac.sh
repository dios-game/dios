#! /bin/bash

cd ..
# ##### 提示：读取配置文件 #####
if [ -f ../config.sh ]; then
	config_file=../config.sh;
elif [ -f ../../config.sh ]; then
	config_file=../../config.sh;
elif [ -f ../../../config.sh ]; then
	config_file=../../../config.sh;
elif [ -f ../../../../config.sh ]; then
	config_file=../../../../config.sh;
elif [ -f ../../../../../config.sh ]; then
	config_file=../../../../../config.sh;
elif [ -f ../../../../../../config.sh ]; then
	config_file=../../../../../../config.sh;
elif [ -f ../../../../../../../config.sh ]; then
	config_file=../../../../../../../config.sh;
fi
source ${config_file}

if [ ! -d proj.mac ]; then
	mkdir proj.mac;
fi
cd proj.mac

function check()
{
	if [[ ! $1 == 0 ]]; then
		echo "\033[31msetup failed\033[0m"
		exit
	fi
}

echo "#####提示：开始构建#####"
cmake -GXcode -DDIOS_CMAKE_PLATFORM=MAC -DCMAKE_TOOLCHAIN_FILE=${DIOS_CMAKE}/toolchain/mac/mac.toolchain.cmake ..
check $?
cmake -GXcode -DDIOS_CMAKE_PLATFORM=MAC -DCMAKE_TOOLCHAIN_FILE=${DIOS_CMAKE}/toolchain/mac/mac.toolchain.cmake ..
check $?
echo "#####提示：构建结束#####"

echo "#####提示：开始编译#####"
xcodebuild -target ALL_BUILD -configuration Debug
xcodebuild -target ALL_BUILD -configuration Release
check $?
echo "#####提示：编译结束#####"

echo "#####提示：开始安装#####"
cmake -DBUILD_TYPE="Debug" -P cmake_install.cmake
cmake -DBUILD_TYPE="Release" -P cmake_install.cmake
check $?
echo "#####提示：安装结束#####"

cmake -P dios_cmake_compile_succeeded.cmake
cmake -P dios_cmake_install_succeeded.cmake