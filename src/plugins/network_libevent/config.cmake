

set(DIOS_CONFIG_TEMPLATE lib)
SET(DIOS_CONFIG_MODULE network_libevent) 


# 
# 初始化工程, 配置基本变量;
# 
MACRO(dios_config_module_init MODULE)
	
	#
	# 1. 基本属性配置;
	#
	SET(DIOS_MODULE_${MODULE}_ANDROID_NAME ${MODULE})
	SET(DIOS_MODULE_${MODULE}_APP_NAME ${MODULE}) 
	
	

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
	SET(DIOS_MODULE_${MODULE}_PRECOMPILED true)
	SET(DIOS_MODULE_${MODULE}_PREBUILT false)

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
	# dios_module_link_library(${MODULE} foo false)
	dios_module_link_library(${MODULE} dios_util false)
	dios_module_link_library(${MODULE} dios_com false)
	# dios_module_link_library(${MODULE} lua false)
	# dios_module_link_library(${MODULE} tolua false)
	# dios_module_link_library(${MODULE} gtest false)
	dios_module_link_library(${MODULE} pthread false)
	# dios_module_link_library(${MODULE} dl false)
	# dios_module_link_library(${MODULE} socket false)
	# dios_module_link_library(${MODULE} xml2 false)
	# dios_module_link_library(${MODULE} z false)
	# dios_module_link_library(${MODULE} inet false)
	# dios_module_link_library(${MODULE} vld false)
	dios_module_link_library(${MODULE} libevent false)

ENDMACRO()


# 
# 导出模块的library和头文件目录;
# 
MACRO(dios_config_find_module MODULE)

	# 
	#  dios_find_module(<module>
	#    [PACKAGE <package>]
	#    [COMPONENTS <component...>]
	#    [HEADERS <path>])
	# 

	dios_find_module(${MODULE})

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
