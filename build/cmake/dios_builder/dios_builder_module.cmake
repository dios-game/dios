
# 
# - DIOS_BUILDER_MODULE: 当前模块
# 
INCLUDE(dios_module)
INCLUDE(dios_builder_module_includes)
INCLUDE(dios_builder_module_definitions)
INCLUDE(dios_builder_module_libraries)
INCLUDE(dios_builder_module_sources)
INCLUDE(dios_builder_module_precompiled)
INCLUDE(dios_builder_module_install)
include(dios_builder_module_setup)
include(dios_builder_module_link)
INCLUDE(dios_builder_module_create_compile_succeeded_cmake)
INCLUDE(dios_builder_module_create_install_succeeded_cmake)

# 
# 创建当前模块;
# 
MACRO(_dios_builder_module_create MODULE MODULE_DIRECTORY)	
	IF(NOT DIOS_MODULE_${MODULE})		
		_dios_module_create(${MODULE} ${MODULE_DIRECTORY})
		_dios_module_link_inherit(${MODULE})
		_dios_module_gen_link_list(${MODULE})		
	ENDIF()
	SET(DIOS_BUILDER_MODULE ${MODULE})
	MESSAGE(STATUS "")
ENDMACRO()
# 
# 
# 
MACRO(_dios_builder_module_pre_build)

	# 执行配置接口;
	INCLUDE(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_CONFIG_PATH})
	dios_config_module_pre_build()	
	if(EXISTS ${DIOS_CMAKE_TEMPLATE_DIRECTORY}/${DIOS_CONFIG_TEMPLATE}/template.cmake)
		INCLUDE(${DIOS_CMAKE_TEMPLATE_DIRECTORY}/${DIOS_CONFIG_TEMPLATE}/template.cmake)
		dios_config_template_pre_build()
	endif()

	_dios_builder_module_setup_dirty_link() # 递归设脏并对脏模块安装;	
	
	_dios_builder_module_add_global_includes() # 添加全局头文件;
	_dios_builder_module_add_sources() # 导入源码	
	
	_dios_builder_module_create_compile_succeeded_cmake() 
	_dios_builder_module_create_install_succeeded_cmake()
ENDMACRO()
# 
# 构建;
# 
MACRO(_dios_builder_module_build)

	_dios_builder_module_link_all() # find并添加宏定义，库及头文件
	_dios_builder_module_add_includes() # 导入头文件目录
	_dios_builder_module_add_definitions() # 导入宏定义

	IF( NOT DIOS_MODULE_${DIOS_BUILDER_MODULE}_PREBUILT )
		IF( ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} STREQUAL APPLICATION)
			IF(DIOS_CMAKE_PLATFORM_IOS OR DIOS_CMAKE_PLATFORM_MAC)
				# 窗口程序为MACOSX_BUNDLE
				ADD_EXECUTABLE(${DIOS_BUILDER_MODULE} MACOSX_BUNDLE ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_SOURCES} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_RESOURCES})
				# SET_MODULE_PROPERTIES( ${DIOS_BUILDER_MODULE} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${DIOS_PROJECT_TEMPLATES_DIRECTORY}/app_window/in/IosInfo.plist.in)
			ELSE()				
				ADD_EXECUTABLE(${DIOS_BUILDER_MODULE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_SOURCES})
			ENDIF()
			_dios_builder_module_exe_copy_to_prebuilt()
		ELSEIF( ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} STREQUAL SHARED )
			ADD_LIBRARY(${DIOS_BUILDER_MODULE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_SOURCES})
			_dios_builder_module_lib_copy_to_prebuilt()
		ELSEIF( ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} STREQUAL STATIC )
			ADD_LIBRARY(${DIOS_BUILDER_MODULE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_SOURCES})
			_dios_builder_module_lib_copy_to_prebuilt()
		ENDIF()
	ENDIF()

	_dios_builder_module_copy_to_install()
ENDMACRO()

# 
# 构建后;
# 
MACRO(_dios_builder_module_post_build)

	# 执行配置接口;
	INCLUDE(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_CONFIG_PATH})
	dios_config_module_post_build()
	if(EXISTS ${DIOS_CMAKE_TEMPLATE_DIRECTORY}/${DIOS_CONFIG_TEMPLATE}/template.cmake)
		INCLUDE(${DIOS_CMAKE_TEMPLATE_DIRECTORY}/${DIOS_CONFIG_TEMPLATE}/template.cmake)
		dios_config_template_post_build()
	endif()

	# 导入库;
	_dios_builder_module_link_libraries()

	# 是否采用预编译头
	IF(DIOS_MODULE_${DIOS_BUILDER_MODULE}_PRECOMPILED)
		# MESSAGE(FATAL_ERROR "DIOS_MODULE_${DIOS_BUILDER_MODULE}_PRECOMPILED:${DIOS_MODULE_${DIOS_BUILDER_MODULE}_PRECOMPILED}")
		_dios_builder_module_use_precompiled()
	ENDIF()
ENDMACRO()
