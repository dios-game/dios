# - Create launchers to set working directory, env. vars, etc.
# 
#  include(dios_find) - to make these available
# 
#  dios_find_module(<module>
#    [PACKAGE <package>]
#    [COMPONENTS <component...>]
#    [HEADER <path>])

# 
# 封装过的boost搜索
# 
MACRO( dios_find_boost )

	_dios_configure_boost()

	find_package(Boost COMPONENTS ${ARGN})

	if(NOT Boost_FOUND)
		message(FATAL_ERROR ">>> [${DIOS_BUILDER_MODULE}] find_boost: boost<${ARGN}> NOT FOUND")
	endif()

	dios_find_add_libraries(boost ${Boost_LIBRARIES})
	dios_find_add_includes(boost ${Boost_INCLUDE_DIR})
ENDMACRO()

# 
# 配置基本环境;
# 
MACRO(_dios_configure_boost)	

	# 设定搜索版本-----------------------------------------
	set(Boost_ADDITIONAL_VERSIONS "1.55" "1.55.0" "1.50" "1.50.0"  "1.49" "1.49.0" "1.48" "1.48.0" "1.47" "1.47.0" "1.46" "1.46.0" "1.46.1" "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )

	set(BOOST_PREBUILT_DIRECTORY ${DIOS_MODULE_boost_DIRECTORY}/prebuilt)

	# 设定头文件目录和库文件目录---------------------------
	set(BOOST_INCLUDEDIR "${BOOST_PREBUILT_DIRECTORY}/inc")

	# ADD_DEFINITIONS( -DBOOST_ALL_NO_LIB )
	IF(DIOS_CMAKE_PLATFORM_WIN32 OR DIOS_CMAKE_PLATFORM_WIN64)
		# 设定选用库的编译类型，以下为动态多线程MD--------------------
		set(Boost_USE_STATIC_LIBS        OFF)
		set(Boost_USE_MULTITHREADED      ON)
		set(Boost_USE_STATIC_RUNTIME     OFF)
		ADD_DEFINITIONS( -DBOOST_ALL_DYN_LINK )
		set(BOOST_LIBRARYDIR "${BOOST_PREBUILT_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/boost")
		# message(FATAL_ERROR ">>> [${DIOS_BUILDER_MODULE}] find_boost: ${BOOST_PREBUILT_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/boost")
	ELSEIF(DIOS_CMAKE_PLATFORM_UNIX)
		# 设定选用库的编译类型，以下为动态多线程MD--------------------
		set(Boost_USE_STATIC_LIBS        OFF)
		set(Boost_USE_MULTITHREADED      ON)
		set(Boost_USE_STATIC_RUNTIME     OFF)
		ADD_DEFINITIONS( -DBOOST_ALL_DYN_LINK )
		set(BOOST_LIBRARYDIR "${BOOST_PREBUILT_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}")
	ELSEIF(DIOS_CMAKE_PLATFORM_IOS)
		# 设定选用库的编译类型，以下为静态多线程MD--------------------
		set(Boost_USE_STATIC_LIBS        ON)
		set(Boost_USE_MULTITHREADED      ON)
		set(Boost_USE_STATIC_RUNTIME     ON)
		set(BOOST_LIBRARYDIR "${BOOST_PREBUILT_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}")
	ELSEIF(DIOS_CMAKE_PLATFORM_ANDROID)
		# 设定选用库的编译类型，以下为静态多线程MD--------------------
		set(Boost_USE_STATIC_LIBS        ON)
		set(Boost_USE_MULTITHREADED      ON)
		set(Boost_USE_STATIC_RUNTIME     ON)
		set(BOOST_LIBRARYDIR "${BOOST_PREBUILT_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}")
	ENDIF()
ENDMACRO()