
# set(DIOS_TARGET_WIN32 true)
# set(DIOS_TARGET_UNIX true)
# set(DIOS_TARGET_IOS true)
# set(DIOS_TARGET_ANDROID true)	

SET(freetype2_FOUND FALSE)

if(DIOS_TARGET_WIN32)
	# 1. 获取头文件;
	find_path(freetype2_INCLUDE_DIR ft2build.h 
		${DIOS_CMAKE_INSTALL_DIRECTORY}/inc/freetype2/win32
		)
elseif(DIOS_TARGET_UNIX)
elseif(DIOS_TARGET_IOS)
	# 1. 获取头文件;
	find_path(freetype2_INCLUDE_DIR ft2build.h 
		${DIOS_CMAKE_INSTALL_DIRECTORY}/inc/freetype2/ios
		)
elseif(DIOS_TARGET_ANDROID)
endif()

# 2. 获取库文件;
find_library( freetype2_LIBRARY_RELEASE freetype
	${DIOS_CMAKE_INSTALL_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/freetype2
	)

find_library( freetype2_LIBRARY_DEBUG freetype
	${DIOS_CMAKE_INSTALL_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/freetype2
	)
		
# 3. 判断是否找到;
IF ( NOT freetype2_INCLUDE_DIR OR NOT freetype2_LIBRARY_RELEASE OR NOT freetype2_LIBRARY_DEBUG)
	SET(freetype2_FOUND FALSE)
	return()
ENDIF()

# 4. 拼凑LIBRARIES
SET( freetype2_LIBRARIES optimized ${freetype2_LIBRARY_RELEASE} debug ${freetype2_LIBRARY_DEBUG} )

# 5. 缓存变量;
IF( freetype2_LIBRARIES )
	set(freetype2_INCLUDE_DIR ${icu_INCLUDE_DIR} CACHE FILEPATH "freetype2 include directory")
	SET(freetype2_FOUND ON CACHE INTERNAL "Whether the freetype2 found")
	set(freetype2_LIBRARIES ${freetype2_LIBRARIES} CACHE FILEPATH "The freetype2  library")
	MARK_AS_ADVANCED( ${freetype2_LIBRARIES} )
ENDIF()
