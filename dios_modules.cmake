
# #
# DIOS 自带模块注册
# #
# 原型
# dios_register_regist_module(module_name module_path)   ==> dios_register_regist_module(module_name module_path module_name) 
# dios_register_regist_module(module_name module_path library1 library2 library3)

# #
# dios_register_regist_module(protobuf dios/src/oslibs/protobuf)
# dios_register_regist_module(libcocos2dx dios/src/oslibs/libcocos2dx cocos2dx cocosdenshion cocos_extension box2d)

# 自定义;
dios_register_regist_module(lib ${CMAKE_CURRENT_LIST_DIR}/templates/lib)
dios_register_regist_module(libfoo ${CMAKE_CURRENT_LIST_DIR}/tests/libfoo)
dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/libs/dios_util)
dios_register_regist_module(dios_com ${CMAKE_CURRENT_LIST_DIR}/src/libs/dios_com)
dios_register_regist_module(crash_handler ${CMAKE_CURRENT_LIST_DIR}/src/libs/crash_handler)

# 插件;
dios_register_regist_module(log_log4cplus ${CMAKE_CURRENT_LIST_DIR}/src/plugins/log_log4cplus)

# 第三方;
dios_register_regist_module(boost ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/boost 
	boost_atomic
	boost_chrono
	boost_thread 
	boost_system  
	boost_date_time 
	boost_filesystem 
	boost_iostreams 
	boost_program_options
	)
dios_register_regist_module(lua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/lua)
dios_register_regist_module(tolua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/tolua)
dios_register_regist_module(gtest ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/gtest)
dios_register_regist_module(protobuf ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/protobuf)
dios_register_regist_module(lua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/lua)
dios_register_regist_module(tolua ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/tolua)
dios_register_regist_module(log4cplus ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/log4cplus)
dios_register_regist_module(libmysql ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/libmysql)
dios_register_regist_module(libevent ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/libevent)
dios_register_regist_module(google_breakpad ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/google_breakpad)
dios_register_regist_module(libcurl ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/libcurl)
dios_register_regist_module(freetype2 ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/freetype2)
dios_register_regist_module(zlib ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/zlib)
dios_register_regist_module(pbc ${CMAKE_CURRENT_LIST_DIR}/src/oslibs/pbc)

# 第三方预编译;
dios_register_regist_module(platform ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/platform pthread dl socket xml2 z inet vld)

# 预编译;
# dios_register_regist_module(dios_util ${CMAKE_CURRENT_LIST_DIR}/src/prebuilt/dios_util)

# dios_register_regist_module_finish()