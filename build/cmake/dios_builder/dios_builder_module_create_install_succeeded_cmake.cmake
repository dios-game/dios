# 
# 编译成功的MD5
# 
macro(_dios_builder_module_create_install_succeeded_cmake)	
	_dios_module_gen_save_install_md5_code(${DIOS_BUILDER_MODULE} DIOS_TEMP_CODE)
	file(WRITE ${CMAKE_BINARY_DIR}/dios_cmake_install_succeeded.cmake ${DIOS_TEMP_CODE})
endmacro()