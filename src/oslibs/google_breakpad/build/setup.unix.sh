#!/bin/sh

cd $(dirname "$0")
cd ..

cd google-breakpad-read-only
LIBRARY_DIRECTORY=../prebuilt/lib/unix
INCLUDE_DIRECTORY=../prebuilt/inc/google_breakpad
BINARY_DIRECTORY=../prebuilt/bin/unix

mkdir -p "$LIBRARY_DIRECTORY"
mkdir -p "$INCLUDE_DIRECTORY"
mkdir -p "$BINARY_DIRECTORY"

./configure
make

mkdir -p "$INCLUDE_DIRECTORY/client/linux/"{handler,crash_generation,minidump_writer}
mkdir -p ../prebuilt/LICENSES
mkdir -p "$INCLUDE_DIRECTORY/processor"
mkdir -p "$INCLUDE_DIRECTORY/common/linux"
mkdir -p "$INCLUDE_DIRECTORY/google_breakpad/common"
mkdir -p "$INCLUDE_DIRECTORY/third_party/lss"

cp -p src/client/linux/*.a "$LIBRARY_DIRECTORY"
cp -p src/client/linux/handler/exception_handler.h "$INCLUDE_DIRECTORY"
cp -p src/client/linux/handler/minidump_descriptor.h "$INCLUDE_DIRECTORY/client/linux/handler"
cp -p src/client/linux/crash_generation/*.h "$INCLUDE_DIRECTORY/client/linux/crash_generation"
cp -p src/client/linux/minidump_writer/*.h "$INCLUDE_DIRECTORY/client/linux/minidump_writer"
cp -p src/processor/scoped_ptr.*h "$INCLUDE_DIRECTORY/processor"
cp -p src/tools/linux/dump_syms/dump_syms "$BINARY_DIRECTORY"
cp -p src/processor/minidump_stackwalk "$BINARY_DIRECTORY"
cp -p COPYING ../prebuilt/LICENSES/google_breakpad.txt
cp -p src/common/linux/*.h "$INCLUDE_DIRECTORY/common/linux"
cp -p src/common/*.h "$INCLUDE_DIRECTORY/common"
cp -p src/google_breakpad/common/*.h "$INCLUDE_DIRECTORY/google_breakpad/common"
cp -p src/third_party/lss/*.h "$INCLUDE_DIRECTORY/third_party/lss"

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