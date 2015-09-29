#!/bin/sh

cd $(dirname "$0")
cd ..

if [ ! -d mysql-connector-c-6.0.2 ]; then
	tar xvf mysql-connector-c-6.0.2.tar.gz;
fi

cd mysql-connector-c-6.0.2;

cmake ./;
make;

mkdir -p ../../../../dependencies/lib/gcc;
cp libmysql/libmysql.so* ../../../../dependencies/lib/gcc/;
cp libmysql/libmysqlclient.so* ../../../../dependencies/lib/gcc/;

mkdir -p ../../../../dependencies/inc/libmysql;
cp include/*.* ../../../../dependencies/inc/libmysql/;

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
cmake -P cmake_install.cmake
if [ $? -ne 0 ]; then
    echo "make install return false!"
    exit 1
fi
cmake -P dios_cmake_compile_succeeded.cmake
cmake -P dios_cmake_install_succeeded.cmake