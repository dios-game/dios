#ifndef DATABASE_DEFINE_CUSTOM_SQL_CLASS_H
#define DATABASE_DEFINE_CUSTOM_SQL_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseDefineCustomSqlClass
{
public:
	static void WriteHeaderDatabaseSqlClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info, const std::string& decl_name);
	static void WriteHeaderDatabaseSqlClassEnd(CCodeFile& file);
	static void WriteHeaderDatabaseSqlClassBegin(CCodeFile& file, const std::string& decl_name);
	static void WriteHeaderDatabaseSqlClassCreateTable(CCodeFile& file);
	static void WriteHeaderDatabaseSqlClassSelectRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceDatabaseSqlClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCreateTable(CCodeFile& file);
	static void WriteSourceSelectResult2Record(CCodeFile& file);
	static void WriteSourceCommitSelectRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceSelectRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceParseFromSqlFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

};

#endif
