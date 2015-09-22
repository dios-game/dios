# 
# 
# 
MACRO(_dios_builder_module_add_definitions)

	dios_current_module_definitions_common()

	IF(DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE STREQUAL "SHARED")
		dios_current_module_definitions_shared()
	ENDIF()

	IF(DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE STREQUAL "SHARED" OR DIOS_MODULE_${DIOS_BUILDER_MODULE}_TYPE STREQUAL "STATIC")
		dios_current_module_definitions_lib()
	ENDIF()

	# 包含头文件
	ADD_DEFINITIONS(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DEFINITIONS})
ENDMACRO()
# 
# 
# 
MACRO(dios_current_module_definitions_common)
		# 平台宏定义
	IF(DIOS_CMAKE_PLATFORM_IOS)		
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -DTARGET_OS_IPHONE )
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -DCC_TARGET_OS_IPHONE )
	ELSEIF(DIOS_CMAKE_PLATFORM_MAC)
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -DTARGET_OS_MAC )
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -DCC_TARGET_OS_MAC )
	ELSEIF(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -we4715 )
		dios_module_add_definitions(${DIOS_BUILDER_MODULE} -Zm200 )
	ENDIF()
ENDMACRO()
# 
# 
# 
MACRO(dios_current_module_definitions_lib)
	dios_module_add_definitions(${DIOS_BUILDER_MODULE} -D${DIOS_MODULE_${DIOS_BUILDER_MODULE}_UPPER}_EXPORT )
ENDMACRO()
# 
# 
# 
MACRO(dios_current_module_definitions_shared)
	dios_module_add_definitions(${DIOS_BUILDER_MODULE} -D${DIOS_MODULE_${DIOS_BUILDER_MODULE}_UPPER}_AS_DLL )
ENDMACRO()
