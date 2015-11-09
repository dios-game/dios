/*
 *	基础类文件定制，用于生成简单的变量操作方法，未来提供给实用Record继承
 */
#ifndef DATABASE_COMMON_CUSTOM_H
#define DATABASE_COMMON_CUSTOM_H

#include <stdio.h>
#include <string>

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseCommonCustom
{
public:
	static void WriteNamespaceBegin(CCodeFile& file, const std::string& table_name);
	static void WriteNamespaceEnd(CCodeFile& file);

	static void WriteHeaderHelperText(CCodeFile& file);
	static void WriteHeaderDefineBegin(CCodeFile& file, const std::string& table_name_upr);
	static void WriteHeaderInclude(CCodeFile& file, const std::string& table_name);
	static void WriteHeaderDefineEnd(CCodeFile& file);

	static void WriteSourceInclude(CCodeFile& file, const std::string& table_name);

	static void WriteSourceFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
	static void WriteFile(const char* output_path, const dios::CDatabaseTableInfo& table_info);
};

#endif
