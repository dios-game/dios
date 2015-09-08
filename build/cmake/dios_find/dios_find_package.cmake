

# 
#  dios_find_module(<module>
#    [PACKAGE <package>]
#    [COMPONENTS <component...>])
# 

MACRO(dios_find_package MODULE )

	SET(DIOS_FIND_MODULE ${MODULE})
	_dios_find_process_args(${ARGN})

	MESSAGE(STATUS ">> DIOS_FIND_MODULE: ${DIOS_FIND_MODULE}")
	MESSAGE(STATUS ">> DIOS_FIND_ARG_PACKAGE: ${DIOS_FIND_ARG_PACKAGE}")
	MESSAGE(STATUS ">> DIOS_FIND_ARG_COMPONENTS: ${DIOS_FIND_ARG_COMPONENTS}")
	MESSAGE(STATUS ">> find_package(${DIOS_FIND_ARG_PACKAGE} COMPONENTS ${DIOS_FIND_ARG_COMPONENTS})")

	find_package(${DIOS_FIND_ARG_PACKAGE} COMPONENTS ${DIOS_FIND_ARG_COMPONENTS})

	if(NOT ${DIOS_FIND_ARG_PACKAGE}_FOUND)
		message(FATAL_ERROR ">>> [${DIOS_BUILDER_MODULE}] find_${DIOS_FIND_ARG_PACKAGE}: ${DIOS_FIND_ARG_PACKAGE} NOT FOUND")
	endif()

	dios_find_add_libraries(boost ${${DIOS_FIND_ARG_PACKAGE}_LIBRARIES})
	dios_find_add_includes(boost ${${DIOS_FIND_ARG_PACKAGE}_INCLUDE_DIR})

endMACRO()


# 
# 处理参数;
# 
MACRO( _dios_find_package_args_process )

	# MESSAGE(STATUS ">> ${ARGN}")
	set(_NO_WHERE)
	set(_CUR_DEST _NO_WHERE)
	set(_VAL_ARGS
		PACKAGE
		COMPONENTS
		)

	foreach(_ARG ${_VAL_ARGS})
		set(${_ARG})
	endforeach()

	foreach(_ELEMENT ${ARGN})
		list(FIND _VAL_ARGS "${_ELEMENT}" _VAL_ARG_FIND)
		list(FIND _BOOL_ARGS "${_ELEMENT}" _BOOL_ARG_FIND)
		if("${_VAL_ARG_FIND}" GREATER "-1")
			set(_CUR_DEST "${_ELEMENT}")
		elseif("${_BOOL_ARG_FIND}" GREATER "-1")
			set("${_ELEMENT}" ON)
			set(_CUR_DEST _NO_WHERE)
		else()
			list(APPEND ${_CUR_DEST} "${_ELEMENT}")
		endif()
	endforeach()

	if(PACKAGE)
		SET(DIOS_FIND_ARG_PACKAGE ${PACKAGE})
	else()
		SET(DIOS_FIND_ARG_PACKAGE ${DIOS_FIND_MODULE})
	endif()

	if(COMPONENTS)
		SET(DIOS_FIND_ARG_COMPONENTS ${COMPONENTS})
	else()
		SET(DIOS_FIND_ARG_COMPONENTS ${DIOS_FIND_MODULE})
	endif()
	
	if(HEADERS)
		SET(DIOS_FIND_ARG_HEADERS ${HEADERS})
	else()
		SET(DIOS_FIND_ARG_HEADERS ${DIOS_FIND_MODULE}/${DIOS_FIND_MODULE}_lib.h)
	endif()

ENDMACRO( _dios_find_package_args_process )

