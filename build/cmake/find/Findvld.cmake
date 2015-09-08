if(DIOS_TARGET_WIN32)
	find_path( vld_INCLUDE_DIR vld/vld.h
			${DIOS_CMAKE_INSTALL_DIRECTORY}/inc
			)
	
	find_library( vld_LIBRARIES vld
			${DIOS_CMAKE_INSTALL_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/oslibs
			)
endif()