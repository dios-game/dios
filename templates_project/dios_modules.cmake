
# #
# Dios自带模块注册
# #
# 原型
# dios_register_regist_module(module_name module_path)   ==> dios_register_regist_module(module_name module_path module_name) 

# dios_register_regist_module(module_name module_path library1 library2 library3)

# #
# dios_register_regist_module(libcocos2dx dios/src/oslibs/libcocos2dx cocos2dx cocosdenshion cocos_extension box2d)

# 自定义;
# dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/libs/dios_util)

# 第三方;
# dios_register_regist_module(lua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/lua)

# 第三方预编译;
# dios_register_regist_module(platform ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/platform pthread dl socket xml2 z inet vld)

# 预编译;
# dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/dios_util)

# dios_register_regist_module_finish()