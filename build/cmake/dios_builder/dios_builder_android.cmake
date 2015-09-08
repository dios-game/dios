# 
# dios_builder_build_module: CMakeLists.txt中使用
# 
INCLUDE(dios_module)
INCLUDE(dios_builder_module)

# 
# 构建
# 
MACRO(dios_builder_android_build_module MODULE MODULE_DIR)
	_dios_builder_android_pre_build(${MODULE} ${MODULE_DIR})
	_dios_builder_android_build()
	_dios_builder_android_post_build()
ENDMACRO()

# 
# 准备构建
# 
MACRO(_dios_builder_android_pre_build MODULE MODULE_DIR)

	# 创建模块;
	_dios_builder_module_create(${MODULE} ${MODULE_DIR})

	# 构建模块;
	_dios_builder_module_pre_build()

	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] build modules: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST}")
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] build includes: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_INCLUDES}")
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] build sources: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_SOURCES}")
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] build libraries: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_LIBRARIES}")
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] build definition: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DEFINITIONS}")
ENDMACRO()

# 
# 开始构建
# 
MACRO(_dios_builder_android_build)
	
	IF( NOT DIOS_MODULE_${DIOS_BUILDER_MODULE}_PREBUILT )
		_dios_builder_android_make_android_mk()
		IF( ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE} STREQUAL SHARED)
			_dios_builder_android_make_application_mk()
		ENDIF()
	ENDIF()	

ENDMACRO()
# 
# 完成构建
# 
MACRO(_dios_builder_android_post_build)

	# 构建后执行模块操作;
	# _dios_builder_module_post_build();
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] done")
	MESSAGE(STATUS "")
ENDMACRO()

# 
# 构建 Android.mk;
# 
macro(_dios_builder_android_make_android_mk)
	
	SET(PROJECT_NAME ${DIOS_BUILDER_MODULE})
	set(PROJECT_DIR ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY})

	# 使用代码创建出一个mk文件;	
	# 生成模块导入字符串;
	MESSAGE(STATUS "[${DIOS_BUILDER_MODULE}] import libraries_name: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST}")
	LIST(LENGTH DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST LEN)
	IF(${LEN} GREATER 0)
		FOREACH(TEMP_MODULE ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST})
			SET(LOCAL_STATIC_LIBRARIES_TEXT "${LOCAL_STATIC_LIBRARIES_TEXT} ${DIOS_MODULE_${TEMP_MODULE}_ANDROID_NAME}")
		ENDFOREACH()
	ENDIF()

	# 生成模块所在目录导入字符串; 此处需要相对目录;  DIOS_CMAKE_PROJECT_DIRECTORY添加到NDK_MODULE_PATH;
	MESSAGE(STATUS "[${DIOS_BUILDER_MODULE}] import module_name: ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST}")
	LIST(LENGTH DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST LEN)
	IF(${LEN} GREATER 0)
		FOREACH(TEMP_MODULE ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST})
			file(RELATIVE_PATH DIOS_TEMP_RELATIVE_PATH ${DIOS_CMAKE_PROJECT_DIRECTORY} ${DIOS_MODULE_${TEMP_MODULE}_DIRECTORY})	
			SET(IMPORT_MODULE_TEXT "${IMPORT_MODULE_TEXT}$(call import-module,${DIOS_TEMP_RELATIVE_PATH}/proj.android/jni)\n")			
		ENDFOREACH()
	ENDIF()

	# 遍历源码目录，生成源码相关的字符串;
	FOREACH(TEMP_SRC_DIRECTORY ${DIOS_SRC_SUB_DIRECTORIES})
		# 头文件路径
		SET(LOCAL_C_INCLUDES_TEXT "${LOCAL_C_INCLUDES_TEXT}${PROJECT_DIR}/${TEMP_SRC_DIRECTORY}\\\n")		
		# 源码
		FOREACH(TEMP_SRC_DIRECTORY_FILE ${DIOS_SRC_SUB_DIRECTORY_FILES_${TEMP_SRC_DIRECTORY}})
			get_filename_component(TEMP_SRC_DIRECTORY_FILE_NAME ${TEMP_SRC_DIRECTORY_FILE} NAME)
			SET(LOCAL_SRC_FILES_TEXT "${LOCAL_SRC_FILES_TEXT}../../${TEMP_SRC_DIRECTORY}/${TEMP_SRC_DIRECTORY_FILE_NAME}\\\n")
		ENDFOREACH()
	ENDFOREACH()

	# DIOS默认头文件包含路径;
	FOREACH(TEMP_SRC_DIRECTORY ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_INCLUDES})
		SET(LOCAL_C_INCLUDES_TEXT "${LOCAL_C_INCLUDES_TEXT}${TEMP_SRC_DIRECTORY}\\\n")
	ENDFOREACH()

	# MESSAGE(FATAL_ERROR "DIOS_MODULE_${DIOS_BUILDER_MODULE}_INCLUDES:${DIOS_MODULE_${DIOS_BUILDER_MODULE}_INCLUDES}")
	
	SET(PROJECT_ANDROID_NAME ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_ANDROID_NAME})
	SET(PROJECT_ANDROID_TYPE ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_ANDROID_TYPE})
	SET(PROJECT_ANDROID_DEFINITIONS ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DEFINITIONS}) 
	
	configure_file(
		${DIOS_CMAKE_CORE_DIRECTORY}/in_templates/Android.mk.in
		${PROJECT_DIR}/proj.android/jni/Android.mk
		@ONLY
		)
endmacro()

# 
# 构建 Application.mk
# 
macro(_dios_builder_android_make_application_mk)	
	set(PROJECT_DIR ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY})

	configure_file(
		${DIOS_CMAKE_CORE_DIRECTORY}/in_templates/Application.mk.in
		${PROJECT_DIR}/proj.android/jni/Application.mk
		@ONLY
		)

	configure_file(
		${DIOS_CMAKE_CORE_DIRECTORY}/in_templates/build.bat.in
		${PROJECT_DIR}/proj.android/build.bat
		@ONLY
		)
endmacro()
