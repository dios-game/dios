#ifndef DATABASE_SQL_CUSTOM_COMMIT_RECORD_CLASS_H
#define DATABASE_SQL_CUSTOM_COMMIT_RECORD_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseSqlCustomCommitRecordClass
{
public:
	static void WriteHeaderCommitRecordClassBegin(CCodeFile& file);
	static void WriteHeaderCommitRecordClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderCommitRecordClassDestruct(CCodeFile& file);
	static void WriteHeaderCommitRecordClassIsDirtyFunction(CCodeFile& file);
	static void WriteHeaderCommitRecordClassCommitInsertFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderCommitRecordClassCommitUpdateFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderCommitRecordClassCommitDeleteFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderCommitRecordClassProtectedMember(CCodeFile& file);
	static void WriteHeaderCommitRecordClassEnd(CCodeFile& file);
	static void WriteHeaderCommitRecordClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceCommitRecordClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCommitRecordClassDestruct(CCodeFile& file);
	static void WriteSourceCommitRecordClassCommitInsertFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCommitRecordClassCommitUpdateFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCommitRecordClassCommitDeleteFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceCommitRecordClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif