#ifndef DATABASE_COMMON_CUSTOM_RECORD_DATA_CLASS_H
#define DATABASE_COMMON_CUSTOM_RECORD_DATA_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseCommonCustomRecordDataClass
{
public:
	static void WriteHeaderRecordDataClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassBegin(CCodeFile& file);
	static void WriteHeaderRecordDataClassEnd(CCodeFile& file);
	static void WriteHeaderRecordDataClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassDestruct(CCodeFile& file);
	static void WriteHeaderRecordDataClassPublicDirtyFunction(CCodeFile& file);
	static void WriteHeaderRecordDataClassColFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassParseFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassSerializeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassByteSizeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordDataClassProtectedDirtyFunction(CCodeFile& file);
	static void WriteHeaderRecordDataClassProtectedMember(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);

	static void WriteSourceRecordDataClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordDataClassStruct(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordDataClassDestruct(CCodeFile& file);
	static void WriteSourceRecrodDataClassColFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordDataClassParseFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordDataClassSerializeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceRecordDataClassByteSizeFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif