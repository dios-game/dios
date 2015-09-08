# 
# 
# 注册模块
# 
# dios_register_regist_module(<module> <module_directory> [<component...>])
macro(dios_register_regist_module MODULE MODULE_DIRECTORY)

	# 库列表; 缺省参数没有值则表示模块名就是库名;
	SET(LIBRARY_LIST ${ARGN})
	LIST(LENGTH LIBRARY_LIST LEN)
	IF(${LEN} EQUAL 0)
		LIST(APPEND LIBRARY_LIST ${MODULE})
	ENDIF()	

	# 创建模块;
	MESSAGE(STATUS ">>> [environment] dios_register_regist_module: ${MODULE} ${MODULE_DIRECTORY} ${LIBRARY_LIST}")
	_dios_module_create(${MODULE} ${MODULE_DIRECTORY} ${LIBRARY_LIST})

	# 添加库;
	FOREACH(LIBRARY ${LIBRARY_LIST})
		LIST(APPEND DIOS_REGISTER_LIBRARY_LIST ${LIBRARY})
	ENDFOREACH()

	# 添加模块;
	LIST(APPEND DIOS_REGISTER_MODULE_LIST ${MODULE})
endmacro()
# 
# 安装模块
# 
# dios_register_regist_module_finish()
macro(dios_register_regist_module_finish)

	# 第一轮继承;
	FOREACH(DCRMF_TEMP_MODULE ${DIOS_REGISTER_MODULE_LIST})
		_dios_module_link_inherit(DCRMF_TEMP_MODULE)
	ENDFOREACH()
	
	# 第二轮继承所有的库;
	FOREACH(DCRMF_TEMP_MODULE ${DIOS_REGISTER_MODULE_LIST})
		_dios_module_link_inherit(${DCRMF_TEMP_MODULE})
		_dios_module_gen_link_list(${DCRMF_TEMP_MODULE})
	ENDFOREACH()
	MESSAGE(STATUS " ")
endmacro()

