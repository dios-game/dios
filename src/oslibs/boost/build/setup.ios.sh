#! /bin/bash

cd $(dirname "$0")
cd ..

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

# 解压
BOOST_DEPENDENCIES_FOLDER="boost-1_55"
DIOS_PREBUILT="prebuilt"
cp patch/boost.1.55.0 ${BOOST_DEPENDENCIES_FOLDER}/

chmod 777 ${DIOS_PREBUILT}/inc
if [ ! -d "${DIOS_PREBUILT}/inc" ]; then
mkdir ${DIOS_PREBUILT}/inc;
fi

if [ ! -d "${DIOS_PREBUILT}/lib/ios" ]; then
mkdir ${DIOS_PREBUILT}/lib/ios;
fi


if [ ! -d "${DIOS_PREBUILT}/bin/ios" ]; then
mkdir ${DIOS_PREBUILT}/bin/ios;
fi

sh boost.sh

cp -rf ios/prefix/lib/* ${${DIOS_PREBUILT}}/lib/ios/
cp -rf ios/prefix/include/* ${${DIOS_PREBUILT}}/inc/
