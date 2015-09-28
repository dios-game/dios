#! /bin/bash

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
make;
if [ $? -ne 0 ]; then
    echo "make return false!"
    exit 1
fi
make install;
if [ $? -ne 0 ]; then
    echo "make install return false!"
    exit 1
fi
cmake -P dios_cmake_compile_succeeded.cmake
cmake -P dios_cmake_install_succeeded.cmake


