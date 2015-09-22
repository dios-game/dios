# 
# 
#  功能描述：到${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt查找模块, 查找失败则提示FATAL_ERROR消息。
# 
#  dios_find_module(<module>
#    [PACKAGE <package>]
#    [COMPONENTS <component...>]
#    [HEADERS <path>])
# 
#  输出: DIOS_FIND_<module>_DEFINITIONS; DIOS_FIND_<module>_INCLUDE_DIR; DIOS_FIND_<module>_LIBRARIES; 
# 
# 搜索指定库
# 
# dios_find_module: 查找 ${MODULE}.lib ${MODULE}/${MODULE}_lib.h
# 
MACRO(dios_find_module MODULE )

	SET(DIOS_FIND_MODULE ${MODULE})
	_dios_find_module_args_process(${ARGN})

	MESSAGE(STATUS ">> ")
	MESSAGE(STATUS ">> * dios_find_module ${MODULE}")
	MESSAGE(STATUS ">> ")
	MESSAGE(STATUS ">> DIOS_FIND_MODULE: ${DIOS_FIND_MODULE}")
	MESSAGE(STATUS ">> DIOS_FIND_ARG_PACKAGE: ${DIOS_FIND_ARG_PACKAGE}")
	MESSAGE(STATUS ">> DIOS_FIND_ARG_COMPONENTS: ${DIOS_FIND_ARG_COMPONENTS}")
	MESSAGE(STATUS ">> DIOS_FIND_ARG_HEADERS: ${DIOS_FIND_ARG_HEADERS}")

	# 查找库;
	SET(HEADER_FLAG x)
	FOREACH( TEMP_HEADER ${DIOS_FIND_ARG_HEADERS} )
		MESSAGE(STATUS ">> _dios_find_module_header(${DIOS_FIND_MODULE} ${DIOS_FIND_ARG_PACKAGE} ${TEMP_HEADER})")
		_dios_find_module_header(${DIOS_FIND_MODULE} ${DIOS_FIND_ARG_PACKAGE} ${TEMP_HEADER} ${HEADER_FLAG})
		dios_find_add_includes(${MODULE} ${${DIOS_FIND_ARG_PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR} ${${DIOS_FIND_ARG_PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR}/${DIOS_FIND_ARG_PACKAGE})
		SET(HEADER_FLAG ${HEADER_FLAG}x)
	ENDFOREACH()

	# 查找头文件;
	FOREACH( TEMP_COMPONENT ${DIOS_FIND_ARG_COMPONENTS} )
		MESSAGE(STATUS ">> _dios_find_module_component(${DIOS_FIND_MODULE} ${DIOS_FIND_ARG_PACKAGE} ${TEMP_COMPONENT})")
		_dios_find_module_component(${DIOS_FIND_MODULE} ${DIOS_FIND_ARG_PACKAGE} ${TEMP_COMPONENT})		
		dios_find_add_libraries(${MODULE} ${${DIOS_FIND_ARG_PACKAGE}_${TEMP_COMPONENT}_LIBRARIES})
	ENDFOREACH()

	MESSAGE(STATUS ">> DIOS_FIND_${MODULE}_DEFINITIONS: ${DIOS_FIND_${MODULE}_DEFINITIONS}")
	MESSAGE(STATUS ">> DIOS_FIND_${MODULE}_INCLUDE_DIR: ${DIOS_FIND_${MODULE}_INCLUDE_DIR}")
	MESSAGE(STATUS ">> DIOS_FIND_${MODULE}_LIBRARIES: ${DIOS_FIND_${MODULE}_LIBRARIES}")
	MESSAGE(STATUS ">> ")

ENDMACRO()


MACRO(_dios_find_module_header MODULE PACKAGE MODULE_HEADER_FILE_RELATIVE_PATH HEADER_FLAG)

	if(DIOS_CMAKE_PLATFORM_UNIX OR DIOS_CMAKE_PLATFORM_IOS OR DIOS_CMAKE_PLATFORM_MAC)
		find_path(${PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR ${MODULE_HEADER_FILE_RELATIVE_PATH}
			${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/inc
			/usr/local/include
			/usr/include
			)
	elseif(DIOS_CMAKE_PLATFORM_ANDROID)
		find_host_path( ${PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR  ${MODULE_HEADER_FILE_RELATIVE_PATH}
			"${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/inc"
			)
	else()
		find_path( ${PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR  ${MODULE_HEADER_FILE_RELATIVE_PATH}
			"${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/inc"
			)
	endif()

	if( NOT ${PACKAGE}_${HEADER_FLAG}_INCLUDE_DIR )
		MESSAGE(FATAL_ERROR ">>> [${DIOS_BUILDER_MODULE}] find_${MODULE}_${PACKAGE}_header: ${MODULE_HEADER_FILE_RELATIVE_PATH} NOT FOUND")
	endif()

endMACRO()

MACRO(_dios_find_module_component MODULE PACKAGE COMPONENT)

	set(COMPONENT_DIRECTORY ${DIOS_MODULE_${MODULE}_DIRECTORY}/prebuilt/lib)
	unset(${PACKAGE}_${COMPONENT}_LIBRARIES)
	unset(${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG)
	unset(${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE)

	if( NOT ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE )		
		if(DIOS_CMAKE_PLATFORM_UNIX)		
			if(${COMPONENT} MATCHES "lib.*")	
				string(SUBSTRING ${COMPONENT} 3 -1 TEMP_LIB)						
			else()
				set(TEMP_LIB ${COMPONENT})
			endif()

			# 查找库
			find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${TEMP_LIB}
				PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
				)
		elseif(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)	
			# 在库根目录查找库
			find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${COMPONENT}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
					)					
			find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG ${COMPONENT}d
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
					NO_DEFAULT_PATH 
					)			
			# 在具体目录寻找库
			if( NOT ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE )
				find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${COMPONENT}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}/release
					NO_DEFAULT_PATH 
					)
			endif()
			
			if( NOT ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG )
				find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG ${COMPONENT}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}/debug
					NO_DEFAULT_PATH 
					)
			endif()
		elseif(DIOS_CMAKE_PLATFORM_IOS OR DIOS_CMAKE_PLATFORM_MAC)		
			if(${COMPONENT} MATCHES "lib.*")	
				string(SUBSTRING ${COMPONENT} 3 -1 TEMP_LIB)
						
			else()
				set(TEMP_LIB ${COMPONENT})
			endif()

			# 在库根目录查找库
			find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${TEMP_LIB}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
					NO_DEFAULT_PATH 
					)
					
			find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG ${TEMP_LIB}d
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
					NO_DEFAULT_PATH 
					)
			
			# 在具体目录寻找库
			if( NOT ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE )
				find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${TEMP_LIB}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}/release
					NO_DEFAULT_PATH 
					)
			endif()
			
			if( NOT ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG )
				find_library( ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG ${TEMP_LIB}
					PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}/debug
					NO_DEFAULT_PATH 
					)
			endif()	
		elseif(DIOS_CMAKE_PLATFORM_ANDROID)		
			if(${COMPONENT} MATCHES "lib.*")	
				string(SUBSTRING ${COMPONENT} 3 -1 TEMP_LIB)						
			else()
				set(TEMP_LIB ${COMPONENT})
			endif()

			# 查找库
			find_host_library( ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${TEMP_LIB}
				PATHS ${COMPONENT_DIRECTORY}/${DIOS_CMAKE_COMPILER}
				)
		endif()
	endif()

	_dios_find_fix_libraries(${PACKAGE} ${COMPONENT})

	IF(NOT ${PACKAGE}_${COMPONENT}_LIBRARIES)
		MESSAGE(FATAL_ERROR ">>> [${DIOS_BUILDER_MODULE}] find_${MODULE}_${PACKAGE}_${COMPONENT}_libraries: ${MODULE_HEADER_FILE_RELATIVE_PATH} NOT FOUND")
	ENDIF()
endMACRO()

# 
# 合并查找结果
# 
MACRO(_dios_find_fix_libraries PACKAGE COMPONENT)

	IF (${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG AND ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE)
		# if the generator supports configuration types then set
		# optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
		IF (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
			SET(${PACKAGE}_${COMPONENT}_LIBRARY optimized ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE} debug ${${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG})
		ELSE()
			# if there are no configuration types and CMAKE_BUILD_TYPE has no value
			# then just use the release libraries
			SET(${PACKAGE}_${COMPONENT}_LIBRARY ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE} )
		ENDIF()
		# FIXME: This probably should be set for both cases
		SET(${PACKAGE}_${COMPONENT}_LIBRARIES optimized ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE} debug ${${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG})
	ENDIF()

	# if only the release version was found, set the debug variable also to the release version
	IF (${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE AND NOT ${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG)
		SET(${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE})
		SET(${PACKAGE}_${COMPONENT}_LIBRARY       ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE})
		SET(${PACKAGE}_${COMPONENT}_LIBRARIES     ${${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE})
	ENDIF()

	# if only the debug version was found, set the release variable also to the debug version
	IF (${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG AND NOT ${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE)
		SET(${PACKAGE}_${COMPONENT}_LIBRARY_RELEASE ${${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG})
		SET(${PACKAGE}_${COMPONENT}_LIBRARY         ${${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG})
		SET(${PACKAGE}_${COMPONENT}_LIBRARIES       ${${PACKAGE}_${COMPONENT}_LIBRARY_DEBUG})
	ENDIF()

ENDMACRO()

# 
# 处理参数;
# 
MACRO( _dios_find_module_args_process )

	# MESSAGE(STATUS ">> ${ARGN}")
	set(_NO_WHERE)
	set(_CUR_DEST _NO_WHERE)
	set(_VAL_ARGS
		PACKAGE
		COMPONENTS
		HEADERS
		)
	SET(DIOS_FIND_ARG_PACKAGE)
	SET(DIOS_FIND_ARG_COMPONENTS)
	SET(DIOS_FIND_ARG_HEADERS)

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
		if(NOT HEADERS)
			SET(DIOS_FIND_ARG_HEADERS ${DIOS_FIND_MODULE}/${DIOS_FIND_MODULE}_lib.h)
		endif()
		if(NOT COMPONENTS)
			SET(DIOS_FIND_ARG_COMPONENTS ${DIOS_FIND_MODULE})
		endif()
	endif()

	if(COMPONENTS)
		SET(DIOS_FIND_ARG_COMPONENTS ${COMPONENTS})
	endif()
	
	if(HEADERS)
		SET(DIOS_FIND_ARG_HEADERS ${HEADERS})
	endif()

ENDMACRO( _dios_find_module_args_process )

