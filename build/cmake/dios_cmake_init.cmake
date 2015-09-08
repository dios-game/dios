
# 
# 设置版本的兼容性以避免不必要的警告
# 
if( COMMAND CMAKE_POLICY )
	CMAKE_POLICY( SET CMP0003 NEW )
	CMAKE_POLICY( SET CMP0006 OLD )
	CMAKE_POLICY( SET CMP0011 OLD )
	CMAKE_POLICY( SET CMP0053 OLD )
	CMAKE_POLICY( SET CMP0054 OLD )
endif()

# 
# dios.cmake
# dios的cmake主脚本，提供给框架使用者调用
# 
# 
# 配置CMake变量
# 
SET( DIOS_CMAKE_CORE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} )
SET( DIOS_CMAKE_TOOL_DIRECTORY  ${DIOS_CMAKE_ROOT_DIRECTORY}/build/tools )

# 
# 加载CMake源码目录函数：提供init.cmake初始化对应目录下的内容; 这样做这个文件就干净多了
# 
MACRO(_dios_add_cmake_directory cmake_directory)	
	LIST(APPEND CMAKE_MODULE_PATH ${DIOS_CMAKE_CORE_DIRECTORY}/${cmake_directory})
	IF(EXISTS ${DIOS_CMAKE_CORE_DIRECTORY}/${cmake_directory}/init.cmake)
		INCLUDE(${DIOS_CMAKE_CORE_DIRECTORY}/${cmake_directory}/init.cmake)
	ENDIF()
ENDMACRO()

#
# 添加全局include
#
MACRO(dios_cmake_add_includes)
	LIST(APPEND DIOS_CMAKE_INCLUDES ${ARGN})
ENDMACRO()
# 
# 加载CMake源码目录
# 
_dios_add_cmake_directory(dios_module)
_dios_add_cmake_directory(dios_register)
_dios_add_cmake_directory(dios_builder)
_dios_add_cmake_directory(dios_find)
_dios_add_cmake_directory(util)
_dios_add_cmake_directory(find)
_dios_add_cmake_directory(launcher)
_dios_add_cmake_directory(toolchain)
# 
# 初始化环境;
# 
INCLUDE(${DIOS_CMAKE_CORE_DIRECTORY}/dios_environment.cmake)


