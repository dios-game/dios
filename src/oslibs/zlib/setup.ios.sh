#! /bin/bash

# 加载环境配置
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
fi
bash ${config_file}

# 加载DXM_DEPENDENCIES
DXM_DEPENDENCIES=$(cat var_dxm_dependencies.txt)

# 解压
ZLIB_ZIP_NAME="zlib"
ZLIB_FOLDER="zlib-1.2.8"

if [ ! -d ${ZLIB_FOLDER} ]; then
	tar xvf ${ZLIB_ZIP_NAME}.zip;
fi

# 补丁
# cp -rf patch/* ${ZLIB_FOLDER}/

# 安装静态库
mkdir -p ${DXM_DEPENDENCIES}/lib/ios/zlib/;

# 构建库
cd ${ZLIB_FOLDER}
mkdir -p proj.ios;
cd proj.ios
cmake ..

# 编译库
xcodebuild -target zlib -configuration Debug;
xcodebuild -target zlib -configuration Release;
cp build/Debug-iphoneos/libcocos2dx.a ${DXM_DEPENDENCIES}/lib/ios/libcocos2dx/debug/;
cp build/Release-iphoneos/libcocos2dx.a ${DXM_DEPENDENCIES}/lib/ios/libcocos2dx/release/;
cd ..

# 安装头文件
chmod 777 ${DXM_DEPENDENCIES}/inc
mkdir -p ${DXM_DEPENDENCIES}/inc/zlib/;

cp -rf *.h ${DXM_DEPENDENCIES}/inc/zlib/;
cp -rf proj.ios/*.h ${DXM_DEPENDENCIES}/inc/zlib/;

cd ..;

