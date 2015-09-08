# 
# dios_cmake.cmake
# dios 框架用的cmake主脚本
# DIOS_CMAKE_PROJECT_DIRECTORY
if(NOT DIOS_CMAKE_PROJECT_DIRECTORY)
	SET(DIOS_CMAKE_PROJECT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endif()

if(NOT DIOS_CMAKE_COMPANY_NAME)
	set(DIOS_CMAKE_COMPANY_NAME "zhangdong")
endif()

if(NOT DIOS_CMAKE_INSTALL_DIRECTORY)
SET( DIOS_CMAKE_INSTALL_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR}/install )
IF(WIN32)
	STRING(REPLACE "/" "\\" DIOS_CMAKE_INSTALL_DIRECTORY_WIN32 ${DIOS_CMAKE_INSTALL_DIRECTORY})
ENDIF()
ENDIF()

# 
# 加载库框架; 如果已经是库目录则无需加载;
# 
SET(ENGINE_LIB dios)
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${ENGINE_LIB}/dios_cmake.project.cmake)
	INCLUDE(${CMAKE_CURRENT_LIST_DIR}/${ENGINE_LIB}/dios_cmake.project.cmake)
endif()

# 
# dios-cmake 下的 dios_modules ;
# 
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/dios_cmake.cmake)
	INCLUDE(${CMAKE_CURRENT_LIST_DIR}/dios_cmake.cmake)
endif()

# 
# dios-cmake 下的 dios_modules ;
# 
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/dios_modules.cmake)
	INCLUDE(${CMAKE_CURRENT_LIST_DIR}/dios_modules.cmake)
endif()

# 
# 全局头文件路径
# 
dios_cmake_add_includes(${CMAKE_CURRENT_LIST_DIR}/inc)


# 
# 当前项目目录下，读取cmake结束;
# 
if(${DIOS_CMAKE_PROJECT_DIRECTORY} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
	dios_register_regist_module_finish()
endif()