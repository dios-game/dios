
# #
# DxM自带模块注册
# #
# 原型
# dios_register_regist_module(module_name module_path)   ==> dios_register_regist_module(module_name module_path module_name) 
# dios_register_regist_module(module_name module_path library1 library2 library3)

# #
# dios_register_regist_module(protobuf dxm/src/oslibs/protobuf)
# dios_register_regist_module(libcocos2dx dxm/src/oslibs/libcocos2dx cocos2dx cocosdenshion cocos_extension box2d)

# 自定义;
dios_register_regist_module(lib ${CMAKE_CURRENT_LIST_DIR}/templates/lib)
dios_register_regist_module(libfoo ${CMAKE_CURRENT_LIST_DIR}/tests/libfoo)
dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/libs/dios_util)
dios_register_regist_module(dios_com ${CMAKE_CURRENT_LIST_DIR}/src/libs/dios_com)

# 第三方;
dios_register_regist_module(lua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/lua)
dios_register_regist_module(tolua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/tolua)
dios_register_regist_module(gtest ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/gtest)
dios_register_regist_module(libevent ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/libevent)

# 第三方预编译;
dios_register_regist_module(platform ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/platform pthread dl socket xml2 z inet vld)

# 预编译;
# dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/dios_util)

# dios_register_regist_module_finish()