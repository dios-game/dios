
# 
# 添加头文件
# 
# dios_module_add_includes(MODULE INCLUDE1 INCLUDE2)
MACRO(dios_module_add_includes MODULE)

	# MESSAGE(STATUS "-------------dios_module_add_includes ${MODULE} ${ARGN}")
	FOREACH( TEMP ${ARGN} )
		# 唯一性检测;
		SET(CHECK_UNIQUE TRUE)
		FOREACH(TEMP_VALUE ${DIOS_MODULE_${MODULE}_INCLUDES})
			IF(${TEMP_VALUE} STREQUAL ${TEMP})
				SET(CHECK_UNIQUE FALSE)
				BREAK()
			ENDIF()	
		ENDFOREACH()
		IF(CHECK_UNIQUE)
			LIST( APPEND DIOS_MODULE_${MODULE}_INCLUDES ${TEMP} )
		ENDIF()
	ENDFOREACH()
ENDMACRO()
