# 
# 添加头文件
# 
MACRO(_dios_builder_module_add_includes)
	INCLUDE_DIRECTORIES(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_INCLUDES})
ENDMACRO()

MACRO(_dios_builder_module_add_global_includes)
	# 包含全局头文件;
	dios_module_add_includes( ${DIOS_BUILDER_MODULE} ${DIOS_CMAKE_INCLUDES} )	
ENDMACRO()




