#! /bin/bash

# ���ػ�������
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

# ����DXM_DEPENDENCIES
DXM_DEPENDENCIES=$(cat var_dxm_dependencies.txt)

# ��ѹ
ZLIB_ZIP_NAME="zlib"
ZLIB_FOLDER="zlib-1.2.8"

if [ ! -d ${ZLIB_FOLDER} ]; then
	tar xvf ${ZLIB_ZIP_NAME}.zip;
fi

# ����
# cp -rf patch/* ${ZLIB_FOLDER}/

# ��װ��̬��
mkdir -p ${DXM_DEPENDENCIES}/lib/ios/zlib/;

# ������
cd ${ZLIB_FOLDER}
mkdir -p proj.ios;
cd proj.ios
cmake ..

# �����
xcodebuild -target zlib -configuration Debug;
xcodebuild -target zlib -configuration Release;
cp build/Debug-iphoneos/libcocos2dx.a ${DXM_DEPENDENCIES}/lib/ios/libcocos2dx/debug/;
cp build/Release-iphoneos/libcocos2dx.a ${DXM_DEPENDENCIES}/lib/ios/libcocos2dx/release/;
cd ..

# ��װͷ�ļ�
chmod 777 ${DXM_DEPENDENCIES}/inc
mkdir -p ${DXM_DEPENDENCIES}/inc/zlib/;

cp -rf *.h ${DXM_DEPENDENCIES}/inc/zlib/;
cp -rf proj.ios/*.h ${DXM_DEPENDENCIES}/inc/zlib/;

cd ..;

