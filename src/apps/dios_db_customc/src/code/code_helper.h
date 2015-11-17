#ifndef CODE_HELPER_H
#define CODE_HELPER_H

#include "dios/platform.h"

#include "dios_db_tableinfo.h"

class CCodeHelper
{
public:

	const char* GetColTypeCName(dios::DatabaseColType col_type);
	const char* GetColTypeCNameReadOnly(dios::DatabaseColType col_type);
	const char* GetColTypeEnumName(dios::DatabaseColType col_type);

	const char* GetRecordStructColInitString(const dios::CDatabaseColInfo& col_info);
	const char* GetColByteSizeString(const dios::CDatabaseColInfo& col_info);
	const char* GetColSerializeString(const dios::CDatabaseColInfo& col_info);
	const char* GetColParseString(const dios::CDatabaseColInfo& col_info);

	DS_SINGLETON(CCodeHelper);
};

#define sCodeHelper CCodeHelper::GetInstancePtr()

#endif
