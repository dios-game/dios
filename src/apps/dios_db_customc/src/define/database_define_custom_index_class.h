#ifndef DATABASE_DEFINE_CUSTOM_KEY_CLASS_H
#define DATABASE_DEFINE_CUSTOM_KEY_CLASS_H

class CCodeFile;
namespace dios {
	class CDatabaseIndexInfo;
	class CDatabaseTableInfo;
}

class DatabaseDefineCustomKeyClass
{
public:
	static void WriteHeaderKeyClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info, const std::string& decl_name);
	static void WriteHeaderKeyClassBegin(CCodeFile& file, const char* table_key_name, const std::string& upper_table_key_name, const std::string& decl_name);
	static void WriteHeaderKeyClassEnd(CCodeFile& file);
	static void WriteHeaderKeyClassStruct(CCodeFile& file, const std::string& upper_table_key_name, const dios::CDatabaseIndexInfo& table_index_info, const dios::CDatabaseTableInfo& table_info);
	static void WriteHeaderKeyClassDestruct(CCodeFile& file, const std::string& upper_table_key_name);
	static void WriteHeaderKeyClassMember(CCodeFile& file, const dios::CDatabaseIndexInfo& table_index_info, const dios::CDatabaseTableInfo& table_info);
	
	static void WriteSourceKeyClassStruct(CCodeFile& file, const std::string& upper_table_key_name, const dios::CDatabaseIndexInfo& table_index_info, const dios::CDatabaseTableInfo& table_info);
	static void WriteSourceKeyClassDestruct(CCodeFile& file, const std::string& upper_table_key_name);
	static void WriteSourceKeyClass(CCodeFile& file, const dios::CDatabaseTableInfo& table_info);
};

#endif
