

set(DIOS_CONFIG_TEMPLATE lib)
SET(DIOS_CONFIG_MODULE boost) 


# 
# 初始化工程, 配置基本变量;
# 
MACRO(dios_config_module_init MODULE)
	
	# 
	# 1. 基本属性配置;
	# 
	SET(DIOS_MODULE_${MODULE}_ANDROID_NAME ${MODULE})
	SET(DIOS_MODULE_${MODULE}_APP_NAME ${MODULE}) 
	
	# andorid子库
	SET(DIOS_MODULE_${MODULE}_date_time_ANDROID_NAME boost_date_time)
	SET(DIOS_MODULE_${MODULE}_signals_ANDROID_NAME boost_signals)
	SET(DIOS_MODULE_${MODULE}_system_ANDROID_NAME boost_system)
	SET(DIOS_MODULE_${MODULE}_thread_ANDROID_NAME boost_thread)
	SET(DIOS_MODULE_${MODULE}_chrono_ANDROID_NAME boost_chrono)
	SET(DIOS_MODULE_${MODULE}_atomic_ANDROID_NAME boost_atomic)

	# 模块类型变量; app(APPLICATION); lib(STATIC, SHARED);
	SET(DIOS_MODULE_${MODULE}_TYPE SHARED) # default  pc mac
	SET(DIOS_MODULE_${MODULE}_ANDROID_TYPE STATIC)
	SET(DIOS_MODULE_${MODULE}_IOS_TYPE STATIC) # can only build static library on ios

	# 模块版本;
	SET(DIOS_MODULE_${MODULE}_VERSION_CODE "1")
	SET(DIOS_MODULE_${MODULE}_VERSION_STRING "1.0.1")

	# IOS设置;
	SET(DIOS_MODULE_${MODULE}_IOS_GUI_IDENTIFIER "com.${DIOS_CMAKE_COMPANY}.${MODULE}")
	SET(DIOS_MODULE_${MODULE}_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
	SET(DIOS_MODULE_${MODULE}_IPHONEOS_DEPLOYMENT_TARGET 5.0)

	# 是否使用预编译头
	SET(DIOS_MODULE_${MODULE}_PRECOMPILED false)
	SET(DIOS_MODULE_${MODULE}_PREBUILT true)

	# 
	# 2. 计算md5;
	# dios_module_add_default_md5(${MODULE})
	# 	额外计算默认目录的md5，其中包括src,inc,proto,src.android/cpp,src.ios/cpp,src.win/cpp，src.unix/cpp
	# dios_module_add_directory_md5(${MODULE} patch)
	# 	额外计算工程当前某目录下的MD5为模块MD5
	dios_module_add_default_md5(${MODULE})

	#
	# 3. 导入模块;
	#
	# dios_module_link_library(${MODULE} lib FALSE)
	
	# dios_module_link_library(${MODULE} lib false)
	# dios_module_link_library(${MODULE} libfoo false)
	# dios_module_link_library(${MODULE} dios_util false)
	# dios_module_link_library(${MODULE} dios_com false)
	# dios_module_link_library(${MODULE} lua false)
	# dios_module_link_library(${MODULE} tolua false)
	# dios_module_link_library(${MODULE} gtest false)
	# dios_module_link_library(${MODULE} libevent false)
	# dios_module_link_library(${MODULE} pthread false)
	# dios_module_link_library(${MODULE} dl false)
	# dios_module_link_library(${MODULE} socket false)
	# dios_module_link_library(${MODULE} xml2 false)
	# dios_module_link_library(${MODULE} z false)
	# dios_module_link_library(${MODULE} inet false)
	# dios_module_link_library(${MODULE} vld false)


ENDMACRO()


# 
# 导出模块的library和头文件目录;
# 
MACRO(dios_config_find_module MODULE)

	#  dios_find_module(<module>
	#    [PACKAGE <package>]
	#    [COMPONENTS <component...>]
	#    [HEADERS <path>])

	SET(LIBRARY_LIST ${ARGN})

	UNSET(BOOST_LIBS)
	# 转换用户模块名称
	FOREACH(TEMP_LIBRARY_NAME ${LIBRARY_LIST})
		IF(TEMP_LIBRARY_NAME MATCHES "boost_filesystem")
			LIST(APPEND BOOST_LIBS filesystem)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_iostreams")
			LIST(APPEND BOOST_LIBS iostreams)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_chrono")
			LIST(APPEND BOOST_LIBS chrono)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_atomic")
			LIST(APPEND BOOST_LIBS atomic)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_program_options")
			LIST(APPEND BOOST_LIBS program_options)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_python")
			LIST(APPEND BOOST_LIBS python)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_regex")
			LIST(APPEND BOOST_LIBS regex)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_serialization")
			LIST(APPEND BOOST_LIBS serialization)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_signals")
			LIST(APPEND BOOST_LIBS signals)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_system")
			LIST(APPEND BOOST_LIBS system)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_thread")
			LIST(APPEND BOOST_LIBS thread)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_wave")
			LIST(APPEND BOOST_LIBS wave)
		ELSEIF(TEMP_LIBRARY_NAME MATCHES "boost_date_time")
			LIST(APPEND BOOST_LIBS date_time)
		ENDIF()
	ENDFOREACH()
	
	MESSAGE(STATUS "Boost libs: ${BOOST_LIBS}")
	
	IF(DIOS_CMAKE_PLATFORM_WIN32)
		dios_find_boost(${BOOST_LIBS})	
	ELSEIF(DIOS_CMAKE_PLATFORM_UNIX)	
		dios_find_boost(${BOOST_LIBS})
	ELSEIF(DIOS_CMAKE_PLATFORM_ANDORID)
	ELSEIF(DIOS_CMAKE_PLATFORM_IOS)
		dios_find_boost(${BOOST_LIBS})
	ELSE()
		MESSAGE(FATAL "Load ${MODULE} is not match!")
	ENDIF()
ENDMACRO()


# 
# 准备构建项目;
# 
MACRO(dios_config_module_pre_build)

	# 添加target前的事件
	# dios_module_add_definitions(<module> -DDEFINITION1 -DDEFINITION2)
	# dios_module_add_includes(<module> <include...>)
	# 
	# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
	# 

ENDMACRO()

# 
# 构建项目结束，准备链接;
# 
MACRO(dios_config_module_post_build)

	# 
	# 添加target后的事件
	# dios_module_add_libraries(<module> <librariy...>)
	# 

ENDMACRO()
