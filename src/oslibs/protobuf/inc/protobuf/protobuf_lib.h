#ifndef PROTOBUF_LIB_H
#define PROTOBUF_LIB_H

#include "dios/platform.h"

#ifdef PROTOBUF_AS_DLL
	#if  defined ( PROTOBUF_EXPORT )
	#define PROTOBUF_DECL DS_DLL_EXPORT
	#else
	#define PROTOBUF_DECL DS_DLL_IMPORT
	#endif // PROTOBUF_EXPORT
#else
	#define PROTOBUF_DECL
#endif

#endif // PROTOBUF_LIB_H
