
# 
# dios_find_add_definitions
# dios_find_add_includes
# dios_find_add_libraries
# 

# 
# 项目宏支持
# 
# dios_find_add_definitions(MODULE -DDEFINITION1 -DDEFINITION2)
MACRO(dios_find_add_definitions MODULE)
	FOREACH( TEMP ${ARGN} )
		# 唯一性检测;
		SET(CHECK_UNIQUE TRUE)
		FOREACH(TEMP_VALUE ${DIOS_FIND_${MODULE}_DEFINITIONS})
			IF(${TEMP_VALUE} STREQUAL ${TEMP})
				SET(CHECK_UNIQUE FALSE)
				BREAK()
			ENDIF()	
		ENDFOREACH()
		IF(CHECK_UNIQUE)
			LIST( APPEND DIOS_FIND_${MODULE}_DEFINITIONS ${TEMP} )
		ENDIF()
	ENDFOREACH()	
ENDMACRO()

# 
# 添加头文件
# 
# dios_find_add_includes(MODULE INCLUDE1 INCLUDE2)
MACRO(dios_find_add_includes MODULE)

	FOREACH( TEMP ${ARGN} )
		# 唯一性检测;
		SET(CHECK_UNIQUE TRUE)
		FOREACH(TEMP_VALUE ${DIOS_FIND_${MODULE}_INCLUDE_DIR})
			IF(${TEMP_VALUE} STREQUAL ${TEMP})
				SET(CHECK_UNIQUE FALSE)
				BREAK()
			ENDIF()	
		ENDFOREACH()
		IF(CHECK_UNIQUE)
			LIST( APPEND DIOS_FIND_${MODULE}_INCLUDE_DIR ${TEMP} )
		ENDIF()
	ENDFOREACH()
ENDMACRO()

# 
# 添加库文件
# 
# dios_find_add_libraries(MODULE LIBRARIES1 LIBRARIES)
MACRO(dios_find_add_libraries MODULE)

	# 调整ios的包含;
	LIST(APPEND DIOS_FIND_${MODULE}_LIBRARIES ${ARGN})	

ENDMACRO()


