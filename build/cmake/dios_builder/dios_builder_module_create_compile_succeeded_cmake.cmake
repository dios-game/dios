# 
# 编译成功的MD5
# 
macro(_dios_builder_module_create_compile_succeeded_cmake)	
	_dios_module_gen_save_compile_md5_code(${DIOS_BUILDER_MODULE} DIOS_TEMP_CODE)
	file(WRITE ${CMAKE_BINARY_DIR}/dios_cmake_compile_succeeded.cmake ${DIOS_TEMP_CODE})
endmacro()

