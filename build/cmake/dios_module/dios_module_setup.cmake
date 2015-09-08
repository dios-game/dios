# 
# 模块安装并保存MD5
# 
MACRO(dios_module_setup MODULE)
	# 脏模块安装
	_dios_module_try_set_dirty(${MODULE})
	if( DIOS_MODULE_${MODULE}_DIRTY )
		_dios_module_setup_with_platform(${MODULE})
	endif()
ENDMACRO()
# 
# 指定目录安装
# 
function(_dios_module_setup_with_platform MODULE)	
	# 不同平台下的安装文件
	IF(DIOS_CMAKE_PLATFORM_WIN32)
		SET(SETUP_FILE_NAME "setup.win32")
	ELSEIF(DIOS_CMAKE_PLATFORM_WIN64)
		SET(SETUP_FILE_NAME "setup.win64")
	ELSEIF(DIOS_CMAKE_PLATFORM_UNIX)
		SET(SETUP_FILE_NAME "setup.unix")
	ELSEIF(DIOS_CMAKE_PLATFORM_IOS)
		SET(SETUP_FILE_NAME "setup.ios")
	ELSEIF(DIOS_CMAKE_PLATFORM_ANDROID_MK)
		SET(SETUP_FILE_NAME "setup.android.mk")
	ELSEIF(DIOS_CMAKE_PLATFORM_ANDROID)
		SET(SETUP_FILE_NAME "setup.android")
	ENDIF()
	# 正式运行安装文件
	if( EXISTS ${DIOS_MODULE_${MODULE}_DIRECTORY} )
		MESSAGE(STATUS 
		dios_file_bash( ${SETUP_FILE_NAME} ${DIOS_MODULE_${MODULE}_DIRECTORY}/build ))
		dios_file_bash( ${SETUP_FILE_NAME} ${DIOS_MODULE_${MODULE}_DIRECTORY}/build )
	endif()
endfunction()

