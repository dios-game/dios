#ifndef DATABASE_SQL_CUSTOM_H
#define DATABASE_SQL_CUSTOM_H

#include "database_common_custom.h"

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseSqlCustom
{
public:
	static void WriteHeaderHelperText(CCodeFile& file);
	static void WriteHeaderDefineBegin(CCodeFile& file, const std::string& table_name_upr);
	static void WriteHeaderInclude(CCodeFile& file, const std::string& table_name);
	static void WriteNamespaceBegin(CCodeFile& file, const std::string& table_name);
	static void WriteNamespaceEnd(CCodeFile& file);
	static void WriteHeaderDefineEnd(CCodeFile& file);

	static void WriteSourceInclude(CCodeFile& file, const std::string& table_name);

	static void WriteSourceFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
	static void WriteFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
};

#endif
