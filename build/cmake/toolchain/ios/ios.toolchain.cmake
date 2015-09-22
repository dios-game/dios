# Copyright (c) 2014, Ruslan Baratov
# All rights reserved.

if(DEFINED CMAKE_CROSSCOMPILING)
	return()
endif()

set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_32_BIT)" CACHE STRING "Build architecture for iOS")
set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
set(CMAKE_XCODE_ATTRIBUTE_VALID_ARCHS "armv7 armv7s i386")
set(IPHONEOS_ARCHS armv7 armv7s)
set(IPHONESIMULATOR_ARCHS i386)

# 使用c11
set(CMAKE_XCODE_ATTRIBUTE_GCC_C_LANGUAGE_STANDARD "c11")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-c++11-narrowing -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++ -ObjC")
set(CMAKE_SHARED_LINKER_FLAGS "-stdlib=libc++")
