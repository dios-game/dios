# 
# dios_builder_build_module: CMakeLists.txt中使用
# 
INCLUDE(dios_module)
INCLUDE(dios_builder_module)

# 
# 构建
# 
MACRO(dios_builder_build_module MODULE MODULE_DIR)
	_dios_builder_pre_build(${MODULE} ${MODULE_DIR})
	_dios_builder_build()
	_dios_builder_post_build()
ENDMACRO()

# 
# 准备构建
# 
MACRO(_dios_builder_pre_build MODULE MODULE_DIR)

	# 创建模块
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
MACRO(_dios_builder_build)
	
	# 构建;
	_dios_builder_module_build()

ENDMACRO()
# 
# 完成构建
# 
MACRO(_dios_builder_post_build)

	# 构建后执行模块操作;
	_dios_builder_module_post_build()

	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] done")
	MESSAGE(STATUS "")
ENDMACRO()


