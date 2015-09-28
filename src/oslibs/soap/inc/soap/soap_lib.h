#ifndef SOAP_LIB_H
#define SOAP_LIB_H

#include "dios/platform.h"

#ifdef SOAP_AS_DLL
	#if  defined ( SOAP_EXPORT )
	#define SOAP_DECL DS_DLL_EXPORT
	#else
	#define SOAP_DECL DS_DLL_IMPORT
	#endif // SOAP_EXPORT
#else
	#define SOAP_DECL
#endif

#endif // SOAP_LIB_H
