#ifndef DATABASE_DEFINE_CUSTOM_H
#define DATABASE_DEFINE_CUSTOM_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseDefineCustom
{
public:
	static void WriteNamespaceBegin(CCodeFile& file, const std::string& table_name);
	static void WriteNamespaceEnd(CCodeFile& file);

	static void WriteHeaderHelperText(CCodeFile& file);
	static void WriteHeaderDefineBegin(CCodeFile& file, const std::string& table_name_upr);
	static void WriteHeaderInclude(CCodeFile& file, const std::string& table_name, const std::string& proj_name);
	static void WriteHeaderDefineEnd(CCodeFile& file);
	static void WriteHeaderTableInfoMD5(CCodeFile& file, const std::string& table_name_upr, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceInclude(CCodeFile& file, const std::string& table_name);

	static void WriteHeaderFile(const char* out_path, const dios::CDatabaseTableInfo& table_info, const std::string& proj_name);
	static void WriteSourceFile(const char* out_path,const dios::CDatabaseTableInfo& table_info);
	static void WriteFile(const char* out_path, const dios::CDatabaseTableInfo& table_info, const std::string& proj_name);
};

#endif
