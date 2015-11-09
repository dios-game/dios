#ifndef DATABASE_COMMON_CUSTOM_INFO_CLASS_H
#define DATABASE_COMMON_CUSTOM_INFO_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseCommonCustomInfoClass
{
public:
	static void WriteHeaderInfoClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderInfoClassBegin(CCodeFile& file);
	static void WriteHeaderInfoClassEnd(CCodeFile& file);
	static void WriteHeaderInfoClassSetupTableInfoFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderInfoClassGetTableNameFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderInfoClassColCountFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderInfoClassSingleton(CCodeFile& file);
	
	static void WriteSourceInfoClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceInfoClassSetupTableInfoFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif
