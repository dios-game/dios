
include(dios_module_definitions)
include(dios_module_includes)
include(dios_module_libraries)
include(dios_module_link)
include(dios_module_md5)
include(dios_module_setup)

# 
# 新建Module
# 
# _dios_cmake_create_module
MACRO( _dios_module_create MODULE MODULE_DIRECTORY )

	# 初始化;
	_dios_module_init(${MODULE} ${MODULE_DIRECTORY} ${ARGN})

	# 修正类型;
	_dios_module_fix_type(${MODULE})
ENDMACRO()

# 
# 模块初始化;
# 
MACRO( _dios_module_init MODULE MODULE_DIRECTORY )

	string(TOUPPER ${MODULE} DIOS_MODULE_${MODULE}_UPPER)
	SET(DIOS_MODULE_${MODULE}_TYPE STATIC) # STATIC SHARED APPLICATION
	SET(DIOS_MODULE_${MODULE}_PRECOMPILED false)
	SET(DIOS_MODULE_${MODULE}_APP_NAME 游戏)
	SET(DIOS_MODULE_${MODULE}_VERSION_CODE 1)
	SET(DIOS_MODULE_${MODULE}_VERSION_STRING 1.0.1)
	SET(DIOS_MODULE_${MODULE}_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
	SET(DIOS_MODULE_${MODULE}_IPHONEOS_DEPLOYMENT_TARGET 5.0)
	SET(DIOS_MODULE_${MODULE}_ANDROID_NAME android_name)
	SET(DIOS_MODULE_${MODULE} ${MODULE})
	SET(DIOS_MODULE_${MODULE}_DIRECTORY ${MODULE_DIRECTORY})
	SET(DIOS_MODULE_${MODULE}_CONFIG_PATH ${DIOS_MODULE_${MODULE}_DIRECTORY}/config.cmake)


	# 该模块所包含的库; 注册时引入;
	SET(LIBRARY_LIST ${ARGN})
	FOREACH(LIBRARY ${LIBRARY_LIST})		
		SET(DIOS_MODULE_${LIBRARY}_MODULE ${MODULE})		
		LIST(APPEND DIOS_MODULE_${MODULE}_LIBRARY_LIST ${LIBRARY})
	ENDFOREACH()

	# 加载配置并执行模块初始化;
	IF(EXISTS ${DIOS_MODULE_${MODULE}_CONFIG_PATH})
		INCLUDE(${DIOS_MODULE_${MODULE}_CONFIG_PATH})
		dios_config_module_init(${MODULE}) # 初始化各种变量;
		_dios_module_try_set_dirty(${MODULE})
	ENDIF()

ENDMACRO()

# 
# 在调用config.cmake的初始化之后调用;
# 
MACRO( _dios_module_fix_type MODULE )

	# ANDROID与IOS特殊做;
	IF(DIOS_CMAKE_PLATFORM_ANDROID)
		IF(DIOS_MODULE_${MODULE}_ANDROID_TYPE)
			SET(DIOS_MODULE_${MODULE}_TYPE ${DIOS_MODULE_${MODULE}_ANDROID_TYPE})
		ELSE()
			SET(DIOS_MODULE_${MODULE}_TYPE STATIC)
		ENDIF()
	ELSEIF(DIOS_CMAKE_PLATFORM_IOS)
		IF(DIOS_MODULE_${MODULE}_IOS_TYPE)
			SET(DIOS_MODULE_${MODULE}_TYPE ${DIOS_MODULE_${MODULE}_IOS_TYPE})
		ELSE()
			SET(DIOS_MODULE_${MODULE}_TYPE STATIC)
		ENDIF()
	ENDIF()
ENDMACRO()
