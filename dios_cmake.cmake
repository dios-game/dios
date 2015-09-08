
# 
# dios_cmake.cmake
# dios框架用的cmake主脚本
# DIOS_CMAKE_ROOT_DIRECTORY
# dios_cmake.cmake放在最外面的原因是因为这里才能获得 DIOS_CMAKE_ROOT_DIRECTORY
IF(NOT DIOS_CMAKE_PROJECT_DIRECTORY)
	SET(DIOS_CMAKE_PROJECT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
ENDIF()

SET( DIOS_CMAKE_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} )
SET( DIOS_CMAKE_TEMPLATE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/templates )

# 
# 加载DIOS框架
# 
INCLUDE(${DIOS_CMAKE_ROOT_DIRECTORY}/build/cmake/dios_cmake_init.cmake)

# 
# 全局变量打印
# 
MACRO( dump_var var)
	MESSAGE(STATUS ">>> [environment] ${var}:${${var}}")
ENDMACRO()

FUNCTION( dump_string var)
	MESSAGE(STATUS ">>> [environment] ${var}")
ENDFUNCTION()

FUNCTION( _dump_newline)
	MESSAGE(STATUS " ")
ENDFUNCTION()

_dump_newline()
dump_string(" ------------- PLATFORM -------------")
dump_var(DIOS_CMAKE_PLATFORM)
dump_var(DIOS_CMAKE_COMPILER)
dump_string(" ------------- ENVIRONMENT DIRECTORY -------------")
dump_var(DIOS_CMAKE_PROJECT_DIRECTORY)
dump_var(DIOS_CMAKE_ROOT_DIRECTORY)
dump_var(DIOS_CMAKE_CORE_DIRECTORY)
dump_var(DIOS_CMAKE_TOOL_DIRECTORY)
_dump_newline()