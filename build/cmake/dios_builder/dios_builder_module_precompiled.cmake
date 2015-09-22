##################################################################
# Support macro to use a precompiled header
# Usage:
#   use_precompiled_header(CURRENT_MODULE HEADER_FILE SRC_FILE)
##################################################################

# 
# 框架下的预编译环境
# 
macro(_dios_builder_module_use_precompiled)

	if(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		_dios_builder_module_use_precompiled_win(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/src/precompiled.h ${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/src/precompiled.cpp)
	elseif(DIOS_CMAKE_PLATFORM_IOS OR DIOS_CMAKE_PLATFORM_MAC)
		_dios_builder_module_use_precompiled_mac_ios(${DIOS_MODULE_${DIOS_BUILDER_MODULE}_DIRECTORY}/src.ios/cpp/Prefix.pch)
	endif()
endmacro()
# 
# 
# 
macro(_dios_builder_module_use_precompiled_win HEADER_FILE SRC_FILE)
	get_filename_component(HEADER ${HEADER_FILE} NAME)
	if(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		add_definitions(/Yu"${HEADER}")
		set_source_files_properties(${SRC_FILE} PPROPERTIES COMPILE_FLAGS /Yc"${HEADER}")
	else()
		MESSAGE(FATAL_ERROR "only DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64 can run 'use_precompiled_header'")
	endif()
endmacro()
# 
# 
# 
macro(_dios_builder_module_use_precompiled_mac_ios PCH_FILE)                  
    set_target_properties(
        ${CURRENT_MODULE} 
        PROPERTIES
        XCODE_ATTRIBUTE_GCC_PREFIX_HEADER ${PCH_FILE}
        XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")
endmacro()
