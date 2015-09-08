
# 加载配置;
include(${CMAKE_CURRENT_LIST_DIR}/config.cmake)

# 设置项目;
SET(DIOS_PROJECT_CURRENT_MODULE ${DIOS_CONFIG_MODULE}) # 设置项目; 为什么不直接用DIOS_CONFIG_MODULE? DIOS_CONFIG_MODULE会每次加载配置的时候都会重置.

# 添加9层目录，只为加载dios_cmake;
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../../../../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../../../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/..)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# 包含dios_cmake
include(dios_cmake.project)

# 构建;
dios_builder_build_module(${DIOS_PROJECT_CURRENT_MODULE} ${CMAKE_CURRENT_LIST_DIR})