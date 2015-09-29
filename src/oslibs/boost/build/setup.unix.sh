#! /bin/bash

cd $(dirname "$0")
cd ..

#!/bin/sh
if [ ! -d "boost_1_55_0_linux" ]; then
tar xvf boost_1_55_0.tar.bz2;
mv boost_1_55_0 boost_1_55_0_linux;
fi
cd boost_1_55_0_linux;
if [ ! -f "bjam" ]; then
./bootstrap.sh
fi

if [ ! -d "../prebuilt/inc" ]; then
mkdir ../prebuilt/inc;
fi

if [ ! -d "../prebuilt/lib/unix" ]; then
mkdir ../prebuilt/lib/unix;
fi


if [ ! -d "../prebuilt/bin/unix" ]; then
mkdir ../prebuilt/bin/unix;
fi

# prepair
boost_path=$(pwd);

# --without-python
./bjam -a --without-python threading=multi runtime-link=shared link=shared --exec-prefix=../prebuilt/bin/unix --libdir=../prebuilt/lib/unix  --includedir=../prebuilt/inc install

cd ..;

# do cmake file
cd $(dirname "$0")
cd ..

mkdir proj.unix;
cd  proj.unix;
cmake -DDIOS_CMAKE_PLATFORM=UNIX ..;
if [ $? -ne 0 ]; then
    echo "cmake return false!"
    exit 1
fi
cmake -DDIOS_CMAKE_PLATFORM=UNIX ..;
if [ $? -ne 0 ]; then
    echo "cmake return false!"
    exit 1
fi
# make;
# if [ $? -ne 0 ]; then
#     echo "make return false!"
#     exit 1
# fi
# make install;
# if [ $? -ne 0 ]; then
#     echo "make install return false!"
#     exit 1
# fi
cmake -P dios_cmake_compile_succeeded.cmake
cmake -P dios_cmake_install_succeeded.cmake
