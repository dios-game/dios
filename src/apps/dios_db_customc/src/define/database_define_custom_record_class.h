#ifndef DATABASE_DEFINE_CUSTOM_RECORD_CLASS_H
#define DATABASE_DEFINE_CUSTOM_RECORD_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseTableInfo;
}

class DatabaseDefineCustomRecrodClass
{
public:
	static void WriteHeaderRecordClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info, const std::string& decl_name);
	static void WriteHeaderRecordClassBegin(CCodeFile& file, const std::string& decl_name);
	static void WriteHeaderRecordClassEnd(CCodeFile& file);
	static void WriteHeaderRecordClassSharedPtr(CCodeFile& file);
	static void WriteHeaderRecordClassDestruct(CCodeFile& file);
	static void WriteHeaderRecordClassColFunction(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderRecordClassCreateFunction(CCodeFile& file);
	static void WriteHeaderRecordClassRTTI(CCodeFile& file);
	
	static void WriteSourceRecordClass(CCodeFile& file);
	static void WriteSourceRecordClassCreateFunction(CCodeFile& file);
};

#endif
