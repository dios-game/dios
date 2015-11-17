#include "precompiled.h"
#include "database_sql_custom.h"

#include "database_sql_custom_commit_record_class.h"
#include "database_sql_custom_commit_object_class.h"
#include "database_define_custom_sql_class.h"

/*
 *	������ʾ
 */
void DatabaseSqlCustom::WriteHeaderHelperText( CCodeFile& file )
{
	file->WriteWithTab(
		"/*\n"
		" * ���ļ��� DatabaseCacheCustom.exe ���ɣ��벻Ҫ�����޸ġ�\n"
		" * ���Ҫ�����ֶ���Ϣ�����޸Ķ�Ӧ�ı������ļ����������ɸ��ļ���\n"
		" */\n");
}

/*
 *	�꿪ͷ
 */
void DatabaseSqlCustom::WriteHeaderDefineBegin( CCodeFile& file, std::string & table_name_upr )
{
	file->WriteWithTab("#ifndef %s_SQL_TBL_H\n", table_name_upr.c_str());
	file->WriteWithTab("#define %s_SQL_TBL_H\n", table_name_upr.c_str());
}

/*
 *	ͷ�ļ�����
 */
void DatabaseSqlCustom::WriteHeaderInclude( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("#include \"%s_com.tbl.h\"\n", table_name.c_str());
	file->WriteWithTab("#include \"database_custom/database_sql_custom.h\"\n");
	file->WriteWithTab("#include \"dxm_util_component/util_component_sql_service_helper.h\"\n");
}

/*
 *	��ͷ
 */
void DatabaseSqlCustom::WriteNamespaceBegin( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("namespace %s_table {\n", table_name.c_str());
}

/*
 *	���β
 */
void DatabaseSqlCustom::WriteNamespaceEnd( CCodeFile& file )
{
	file->WriteWithTab("\n");
	file->WriteWithTab("};\n");
}

/*
 *	���β
 */
void DatabaseSqlCustom::WriteHeaderDefineEnd( CCodeFile& file )
{
	file->WriteWithTab("\n");
	file->WriteWithTab("#endif\n");
}

/*
 *	ͷ�ļ�
 */
void DatabaseSqlCustom::WriteSourceInclude( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("#include \"precompiled.h\"\n");
	file->WriteWithTab("#include \"%s_sql.tbl.h\"\n", table_name.c_str());
}

/*
 *	����CPP�ļ�
 */
void DatabaseSqlCustom::WriteSourceFile( const char * out_path, dios::CDatabaseTableInfo & table_info )
{
	/*
	 *	��ʼ������
	 */
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);

	std::string table_cpp_file = out_path;
	table_cpp_file.append("/");
	table_cpp_file.append(table_name);
	table_cpp_file.append("_sql.tbl.cpp");

	int table_col_count = table_info.GetTableColDescCount();
	int table_key_count = table_info.GetTableKeyDescCount();

	CCodeFile& file = CCodeFile::Create(table_cpp_file);
	XE_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteSourceInclude(file, table_name);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseDefineCustomSqlClass::WriteSourceDatabaseSqlClass(file, table_info);
	file->WriteWithTab("\n");
	DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClass(file, table_info);
	file->WriteWithTab("\n");
	DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClass(file, table_info);
	file->DecreaseTab();
	WriteNamespaceEnd(file);

	XE_SAFE_DELETE(file);
}

void DatabaseSqlCustom::WriteHeaderFile( const char * out_path, dios::CDatabaseTableInfo & table_info )
{
	/*
	 *	��ʼ������
	 */
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);

	std::string table_h_file = out_path;
	table_h_file.append("/");
	table_h_file.append(table_name);
	table_h_file.append("_sql.tbl.h");

	int table_col_count = table_info.GetTableColDescCount();
	int table_key_count = table_info.GetTableKeyDescCount();

	CCodeFile& file = CCodeFile::Create(table_h_file);
	XE_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteHeaderHelperText(file);
	file->WriteWithTab("\n");
	WriteHeaderDefineBegin(file, table_name_upr);
	file->WriteWithTab("\n");
	WriteHeaderInclude(file, table_name);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClass(file, table_info);
	file->WriteWithTab("\n");
	DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClass(file, table_info);
	file->DecreaseTab();
	WriteNamespaceEnd(file);
	WriteHeaderDefineEnd(file);

	XE_SAFE_DELETE(file);
}

/*
 *	�����ļ�
 */
void DatabaseSqlCustom::WriteFile(const char * out_path, dios::CDatabaseTableInfo & table_info) {
	WriteSourceFile(out_path, table_info);
	WriteHeaderFile(out_path, table_info);
}
