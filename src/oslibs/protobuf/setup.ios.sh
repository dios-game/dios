#! /bin/bash

# ¼ÓÔØ»·¾³ÅäÖÃ
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
sh ${config_file}

# ¼ÓÔØDXM_DEPENDENCIES
DXM_DEPENDENCIES=$(cat var_dxm_dependencies.txt)

local_path=$(pwd);


sh protobuf.sh

chmod 777 ${DXM_DEPENDENCIES}/inc
mkdir -p ${DXM_DEPENDENCIES}/lib/ios/libprotobuf/;
cp -rf protobuf/lib/*.a ${DXM_DEPENDENCIES}/lib/ios/libprotobuf/;

mkdir -p ${DXM_DEPENDENCIES}/bin/ios/debug;
mkdir -p ${DXM_DEPENDENCIES}/bin/ios/release;
cp protobuf/bin/protoc ${DXM_DEPENDENCIES}/bin/ios/debug/;
cp protobuf/bin/protoc ${DXM_DEPENDENCIES}/bin/ios/release/;

mkdir -p ${DXM_DEPENDENCIES}/inc/libprotobuf/;
cp -rf protobuf/include/* ${DXM_DEPENDENCIES}/inc/libprotobuf/;

cd ..;