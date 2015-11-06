#ifndef DIOS_DB_TABLE_LIB_H
#define DIOS_DB_TABLE_LIB_H

#include "dios/platform.h"

#ifdef DIOS_DB_TABLE_AS_DLL
	#if  defined ( DIOS_DB_TABLE_EXPORT )
	#define DIOS_DB_TABLE_DECL DS_DLL_EXPORT
	#else
	#define DIOS_DB_TABLE_DECL DS_DLL_IMPORT
	#endif // DIOS_DB_TABLE_EXPORT
#else
	#define DIOS_DB_TABLE_DECL
#endif

#endif // DIOS_DB_TABLE_LIB_H
