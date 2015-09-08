if(DIOS_TARGET_WIN32)
	find_path( pthread_INCLUDE_DIR pthread/pthread.h
			${DIOS_CMAKE_INSTALL_DIRECTORY}/inc
			)
	
	find_library( pthread_LIBRARIES pthreadVCE2
			${DIOS_CMAKE_INSTALL_DIRECTORY}/lib/${DIOS_CMAKE_COMPILER}/oslibs
			)
endif()