# 
# 计算模块MD5
# 
macro(dios_module_add_default_md5 MODULE)
	SET(PROJECT_DIR ${DIOS_MODULE_${MODULE}_DIRECTORY})
	if(EXISTS ${PROJECT_DIR}/inc)
		dios_file_md5dir(${PROJECT_DIR}/inc DIOS_MODULE_${MODULE}_MD5)
	endif()
	
	if(EXISTS ${PROJECT_DIR}/src)
		dios_file_md5dir(${PROJECT_DIR}/src DIOS_MODULE_${MODULE}_MD5)
	endif()		
	
	if(EXISTS ${PROJECT_DIR}/src.win32/cpp)
		dios_file_md5dir(${PROJECT_DIR}/src.win32/cpp DIOS_MODULE_${MODULE}_MD5)
	endif()		
	
	if(EXISTS ${PROJECT_DIR}/src.ios/cpp)
		dios_file_md5dir(${PROJECT_DIR}/src.ios/cpp DIOS_MODULE_${MODULE}_MD5)
	endif()		
	
	if(EXISTS ${PROJECT_DIR}/src.android/cpp)
		dios_file_md5dir(${PROJECT_DIR}/src.android/cpp DIOS_MODULE_${MODULE}_MD5)
	endif()			
	
	if(EXISTS ${PROJECT_DIR}/proto)
		dios_file_md5dir(${PROJECT_DIR}/proto DIOS_MODULE_${MODULE}_MD5)
	endif()
	
	if(EXISTS ${PROJECT_DIR}/tbl)
		dios_file_md5dir(${PROJECT_DIR}/tbl DIOS_MODULE_${MODULE}_MD5)
	endif()

	if(EXISTS ${PROJECT_DIR}/patch)
		dios_file_md5dir(${PROJECT_DIR}/patch DIOS_MODULE_${MODULE}_MD5)
	endif()
endmacro()

# 
# 计算工程下载文件夹MD5
# 
macro(dios_module_add_directory_md5 MODULE DIRECTORY)

	if(IS_ABSOLUTE ${DIRECTORY})
		dios_file_md5dir(${DIRECTORY} DIOS_MODULE_${MODULE}_MD5)
	elseif(EXISTS ${DIOS_MODULE_${MODULE}_DIRECTORY}/${DIRECTORY})
		dios_file_md5dir(${DIOS_MODULE_${MODULE}_DIRECTORY}/${DIRECTORY} DIOS_MODULE_${MODULE}_MD5)
	endif()
endmacro()

macro(dios_module_add_file_md5 MODULE FILE_PATH)
	if(IS_ABSOLUTE ${FILE_PATH})
		dios_file_md5file(${FILE_PATH} DIOS_MODULE_${MODULE}_MD5)
	elseif(EXISTS ${DIOS_MODULE_${MODULE}_DIRECTORY}/${FILE_PATH})
		dios_file_md5file(${DIOS_MODULE_${MODULE}_DIRECTORY}/${FILE_PATH} DIOS_MODULE_${MODULE}_MD5)
	endif()
endmacro()
# 
# 加载安装MD5
# 
macro(_dios_module_load_setup_md5 MODULE)
	set(DIOS_MODULE_${MODULE}_COMPILE_MD5 null)
	if(EXISTS ${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_compile_md5.txt) 
		file(READ ${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_compile_md5.txt DIOS_MODULE_${MODULE}_COMPILE_MD5)
	endif()
	set(DIOS_MODULE_${MODULE}_INSTALL_MD5 null)
	if(EXISTS ${DIOS_CMAKE_INSTALL_DIRECTORY}/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_install_md5.txt) 
		file(READ ${DIOS_CMAKE_INSTALL_DIRECTORY}/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_install_md5.txt DIOS_MODULE_${MODULE}_INSTALL_MD5)
	endif()	
endmacro()

# 
# 保存安装MD5
# 
macro(_dios_module_gen_save_compile_md5_code MODULE RETURN_CODE_VARIABLE)
	SET( ${RETURN_CODE_VARIABLE} 
		"file(WRITE ${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_compile_md5.txt ${DIOS_MODULE_${MODULE}_MD5})"
		)
endmacro()

macro(_dios_module_gen_save_install_md5_code MODULE RETURN_CODE_VARIABLE)
	SET( ${RETURN_CODE_VARIABLE} 
		"file(WRITE ${DIOS_CMAKE_INSTALL_DIRECTORY}/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_install_md5.txt ${DIOS_MODULE_${MODULE}_MD5})"
		)
endmacro()

# 
# 清理安装MD5
# 
macro(_dios_module_clear_setup_md5 MODULE)
	file(WRITE ${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/md5/${DIOS_CMAKE_COMPILER}_${MODULE}_compile_md5.txt null)
endmacro()
# 
# 检查是否改变
# 
macro(_dios_module_try_set_dirty MODULE)

	_dios_module_load_setup_md5(${MODULE})

	if(${DIOS_MODULE_${MODULE}_MD5} MATCHES ${DIOS_MODULE_${MODULE}_COMPILE_MD5})
		SET(DIOS_MODULE_${MODULE}_DIRTY FALSE)
	else()
		SET(DIOS_MODULE_${MODULE}_DIRTY TRUE)
	endif()

	if(NOT DIOS_MODULE_${MODULE}_DIRTY)
		if(${DIOS_MODULE_${MODULE}_MD5} MATCHES ${DIOS_MODULE_${MODULE}_INSTALL_MD5})
			SET(DIOS_MODULE_${MODULE}_DIRTY FALSE)
		else()
			SET(DIOS_MODULE_${MODULE}_DIRTY TRUE)
		endif()
	endif()
	
	# MESSAGE(STATUS "_dios_module_try_set_dirty ${MODULE} {${DIOS_MODULE_${MODULE}_MD5}} {${DIOS_MODULE_${MODULE}_COMPILE_MD5}} {${DIOS_MODULE_${MODULE}_INSTALL_MD5}} ${DIOS_MODULE_${MODULE}_DIRTY}")
endmacro()
