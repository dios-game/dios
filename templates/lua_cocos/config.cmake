

set(DIOS_CONFIG_TEMPLATE console)
SET(DIOS_CONFIG_MODULE dios-lua-app) 


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
	SET(DIOS_MODULE_${MODULE}_TYPE APPLICATION) # default  pc mac
	SET(DIOS_MODULE_${MODULE}_ANDROID_TYPE SHARED)
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
	# dios_module_link_library(${MODULE} dios_util false)
	# dios_module_link_library(${MODULE} dios_com false)
	# dios_module_link_library(${MODULE} lua false)
	# dios_module_link_library(${MODULE} tolua false)
	# dios_module_link_library(${MODULE} gtest false)
	# dios_module_link_library(${MODULE} pthread false)
	# dios_module_link_library(${MODULE} dl false)
	# dios_module_link_library(${MODULE} socket false)
	# dios_module_link_library(${MODULE} xml2 false)
	# dios_module_link_library(${MODULE} z false)
	# dios_module_link_library(${MODULE} inet false)
	# dios_module_link_library(${MODULE} vld false)
	dios_module_link_library(${MODULE} cocos-lua false)

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
	IF(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows")
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -DUNICODE -D_UNICODE)
	ELSEIF(DIOS_CMAKE_PLATFORM_IOS)
		FILE(GLOB DIOS_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/Resources/*)
		set_source_files_properties(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	ELSEIF(DIOS_CMAKE_PLATFORM_MAC)
		FILE(GLOB TEMP_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES_1 ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/src.mac/res/*)
		FILE(GLOB TEMP_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES_2 ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/Resources/*)
		SET(DIOS_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES ${TEMP_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES_1} ${TEMP_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES_2})
		SET_SOURCE_FILES_PROPERTIES(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	ENDIF()

ENDMACRO()

# 
# 构建项目结束，准备链接;
# 
MACRO(dios_config_module_post_build)

	# 
	# 添加target后的事件
	# dios_module_add_libraries(<module> <librariy...>)
	# 
	IF(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		create_target_launcher(${DIOS_BUILDER_MODULE} 
			WORKING_DIRECTORY "$(ProjectDir)"
			LAUNCHER_DIRECTORY ${CMAKE_BINARY_DIR}/output
			LAUNCHER ${DIOS_BUILDER_MODULE}.exe
			)
	ELSEIF(DIOS_CMAKE_PLATFORM_MAC)
		SET_TARGET_PROPERTIES(${DIOS_BUILDER_MODULE} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/src.mac/res/Info.plist)
	ENDIF()
ENDMACRO()
