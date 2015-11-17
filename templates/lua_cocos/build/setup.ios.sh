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

if [ ! -d proj.ios ]; then
	mkdir proj.ios;
fi
cd proj.ios

# #####提示：开始构建#####
cmake -GXcode -DDIOS_CMAKE_PLATFORM=IOS -DCMAKE_TOOLCHAIN_FILE=${DIOS_CMAKE}/toolchain/ios/ios.toolchain.cmake ..
