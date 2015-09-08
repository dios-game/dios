
# 
# DIOS框架用的 dios_builder_module_link_all
# 
macro(_dios_builder_module_link_all)
	FOREACH(DCMAIMIAL_TEMP_MODULE ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_IMPORT_MODULE_LIST})
		_dios_builder_module_link_includes_and_libraries(${DCMAIMIAL_TEMP_MODULE} ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_${DCMAIMIAL_TEMP_MODULE}_IMPORT_LIBRARY_LIST})
	ENDFOREACH()
endmacro()
# 
# DIOS框架用的 _dios_builder_module_link_includes_and_libraries
# 
macro(_dios_builder_module_link_includes_and_libraries MODULE)
	
	# 查看是否存在模块;
	IF(NOT DIOS_MODULE_${MODULE})
		MESSAGE(FATAL_ERROR "${MODULE} Not Found")
		RETURN()
	ENDIF()

	# 库列表; 缺省参数没有值则表示模块名就是库名;
	SET(LIBRARY_LIST ${ARGN})
	LIST(LENGTH LIBRARY_LIST LEN)
	IF(${LEN} EQUAL 0)
		LIST(APPEND LIBRARY_LIST ${MODULE})
	ENDIF()	

	# 查找库;
	INCLUDE(${DIOS_MODULE_${MODULE}_CONFIG_PATH})
	dios_config_find_module(${MODULE} ${LIBRARY_LIST})

	# 查找到了就可以添加头文件目录和库路径;	
	# 导入库XXX_AS_DLL宏
	string(TOUPPER ${MODULE} MODULE_UPPER)
	IF(${DIOS_MODULE_${MODULE}_TYPE} STREQUAL "SHARED")
		dios_module_add_definitions( ${DIOS_BUILDER_MODULE} -D${DIOS_MODULE_${MODULE}_UPPER}_AS_DLL )
	ENDIF()
	# 添加头文件路径与库
	dios_module_add_definitions(${DIOS_BUILDER_MODULE} ${DIOS_FIND_${MODULE}_DEFINITIONS})
	dios_module_add_includes(${DIOS_BUILDER_MODULE} ${DIOS_FIND_${MODULE}_INCLUDE_DIR}) 
	dios_module_add_libraries(${DIOS_BUILDER_MODULE} ${DIOS_FIND_${MODULE}_LIBRARIES})

	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] import MODULE(${MODULE}) includes: ${DIOS_FIND_${MODULE}_INCLUDE_DIR}")
	MESSAGE(STATUS ">>> [${DIOS_BUILDER_MODULE}] import MODULE(${MODULE}) libraries: ${DIOS_FIND_${MODULE}_LIBRARIES}")

endmacro()
