#ifndef LOG_LOG4CPLUS_LIB_H
#define LOG_LOG4CPLUS_LIB_H

#include "dios/platform.h"

#ifdef LOG_LOG4CPLUS_AS_DLL
	#if  defined ( LOG_LOG4CPLUS_EXPORT )
	#define LOG_LOG4CPLUS_DECL DS_DLL_EXPORT
	#else
	#define LOG_LOG4CPLUS_DECL DS_DLL_IMPORT
	#endif // LOG_LOG4CPLUS_EXPORT
#else
	#define LOG_LOG4CPLUS_DECL
#endif

#endif // LOG_LOG4CPLUS_LIB_H
