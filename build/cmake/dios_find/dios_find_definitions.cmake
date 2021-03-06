

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
