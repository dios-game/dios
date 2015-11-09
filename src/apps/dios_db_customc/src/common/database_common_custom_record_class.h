#ifndef DATABASE_COMMON_CUSTOM_RECORD_CLASS_H
#define DATABASE_COMMON_CUSTOM_RECORD_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseCommonCustomRecordClass
{
public:
	static void WriteHeaderRecordClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassBegin(CCodeFile& file);
	static void WriteHeaderRecordClassEnd(CCodeFile& file);
	static void WriteHeaderRecordClassStruct(CCodeFile& file);
	static void WriteHeaderRecordClassDestruct(CCodeFile& file);
	static void WriteHeaderRecordClassColFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassParseFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassSerializeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassByteSizeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassIsCommitNecessaryFunction(CCodeFile& file);
	static void WriteHeaderRecordClassCommitFunction(CCodeFile& file);
	static void WriteHeaderRecordClassSetDeletedFunction(CCodeFile& file);
	static void WriteHeaderRecordClassInitCommitObjectFunction(CCodeFile& file);
	static void WriteHeaderRecordClassRecordDataFunction(CCodeFile& file);
	static void WriteHeaderRecordClassCommitObjectFunction(CCodeFile& file);
	static void WriteHeaderRecordClassProtectedMember(CCodeFile& file);

	static void WriteSourceRecordClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordClassStruct(CCodeFile& file);
	static void WriteSourceRecordClassDestruct(CCodeFile& file);
	static void WriteSourceRecordClassParseFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordClassSerializeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordClassByteSizeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordClassCommitFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordClassSetDeletedFunction(CCodeFile& file);
	static void WriteSourceRecordClassInitCommitObjectFunction(CCodeFile& file);
};

#endif
