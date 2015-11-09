#ifndef DATABASE_DEFINE_CUSTOM_CACHE_CLASS_H
#define DATABASE_DEFINE_CUSTOM_CACHE_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseDefineCustomCacheClass
{
public:
	static void WriteHeaderDatabaseCacheClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info, const std::string& decl_name);
	static void WriteHeaderDatabaseCacheClassBegin(CCodeFile& file, const std::string& decl_name);
	static void WriteHeaderDatabaseCacheClassEnd(CCodeFile& file);
	static void WriteHeaderDatabaseCacheClassCreateTable(CCodeFile& file);
	static void WriteHeaderResult2Record(CCodeFile& file);
	static void WriteHeaderDatabaseCacheClassCacheRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderDatabaseCacheClassSelectRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderDatabaseCacheClassReleaseRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceDatabaseCacheClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCreateTable(CCodeFile& file);
	static void WriteSourceResult2Record(CCodeFile& file);
	static void WriteSourceCacheRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceSelectRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceReleaseRecordSet(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif