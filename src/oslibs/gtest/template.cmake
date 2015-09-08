
# 
# 模板初始化;
# 
MACRO(dios_config_template_init TEMPLATE_MODULE_NAME TEMPLATE_MODULE_DIRECTORY)

	# 
	# 1. 复制模板到模块目录
	# 
	dios_template_make_sure_directory()
	dios_template_copy_directory()
	dios_template_create_config()

	#
	# 2. 创建config.cmake
	#
	# configure_file(
	#		${DIOS_CMAKE_CURRENT_TEMPLATE_DIRECTORY}/inc/lib/lib_lib.h.in
	#		${TEMPLATE_MODULE_DIRECTORY}/inc/${TEMPLATE_MODULE_NAME}/${TEMPLATE_MODULE_NAME}_lib.h
	#		@ONLY
	#		NEWLINE_STYLE UNIX
	#	)

	file(MAKE_DIRECTORY ${TEMPLATE_MODULE_DIRECTORY}/inc/${TEMPLATE_MODULE_NAME})	
	configure_file(
		${DIOS_CMAKE_CURRENT_TEMPLATE_DIRECTORY}/inc/lib/lib_lib.h.in
		${TEMPLATE_MODULE_DIRECTORY}/inc/${TEMPLATE_MODULE_NAME}/${TEMPLATE_MODULE_NAME}_lib.h
		@ONLY
		NEWLINE_STYLE UNIX
		)
	configure_file(
		${DIOS_CMAKE_CURRENT_TEMPLATE_DIRECTORY}/src/lib_lib.cpp.in
		${TEMPLATE_MODULE_DIRECTORY}/src/${TEMPLATE_MODULE_NAME}_lib.cpp
		@ONLY
		NEWLINE_STYLE UNIX
		)

	#
	# 3. 移除无用的文件及目录;
	#
	# dios_file_rmdir(${TEMPLATE_MODULE_DIRECTORY}/${TEMPLATE_MODULE_NAME}/inc/lib)
	# dios_file_rm(${TEMPLATE_MODULE_DIRECTORY}/${TEMPLATE_MODULE_NAME}/src/foo.cpp)
	dios_file_rmdir(${TEMPLATE_MODULE_DIRECTORY}/inc/lib)
	dios_file_rm(${TEMPLATE_MODULE_DIRECTORY}/src/foo.cpp)
	dios_file_rm(${TEMPLATE_MODULE_DIRECTORY}/src/lib_lib.cpp)
	dios_file_rm(${TEMPLATE_MODULE_DIRECTORY}/src/lib_lib.cpp.in)
ENDMACRO()
 
# 
# 使用该模板的模块构建前操作;
# 
MACRO(dios_config_template_pre_build)

	# 
	# dios_module_add_definitions(<module> -DDEFINITION1 -DDEFINITION2)
	# dios_module_add_includes(<module> <include...>)
	# 

ENDMACRO()

# 
# 使用该模板的模块构建后操作;
# 
MACRO(dios_config_template_post_build)

	# 
	# dios_module_add_libraries(<module> <librariy...>)
	# 

ENDMACRO()