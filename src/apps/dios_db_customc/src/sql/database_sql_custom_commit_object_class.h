#ifndef DATABASE_SQL_CUSTOM_COMMIT_OBJECT_CLASS_H
#define DATABASE_SQL_CUSTOM_COMMIT_OBJECT_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseSqlCustomCommitObjectClass
{
public:
	static void WriteHeaderCommitObjectClassBegin(CCodeFile& file);
	static void WriteHeaderCommitObjectClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderCommitObjectClassDestruct(CCodeFile& file);
	static void WriteHeaderCommitObjectClassCommitInsertFunction(CCodeFile& file);
	static void WriteHeaderCommitObjectClassCommitUpdateFunction(CCodeFile& file);
	static void WriteHeaderCommitObjectClassCommitDeleteFunction(CCodeFile& file);
	static void WriteHeaderCommitObjectClassSetRecordIDFunction(CCodeFile& file);
	static void WriteHeaderCommitObjectClassMember(CCodeFile& file);
	static void WriteHeaderCommitObjectClassEnd(CCodeFile& file);
	static void WriteHeaderCommitObjectClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceCommitObjectClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCommitObjectClassDestruct(CCodeFile& file);
	static void WriteSourceCommitObjectClassCommitInsertFunction(CCodeFile& file);
	static void WriteSourceCommitObjectClassCommitUpdateFunction(CCodeFile& file);
	static void WriteSourceCommitObjectClassCommitDeleteFunction(CCodeFile& file);
	static void WriteSourceCommitObjectClassSetRecordIDFunction(CCodeFile& file);
	static void WriteSourceCommitObjectClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif