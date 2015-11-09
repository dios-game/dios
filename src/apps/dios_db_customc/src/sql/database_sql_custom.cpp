#include "precompiled.h"
#include "database_sql_custom.h"

#include "database_sql_custom_commit_record_class.h"
#include "database_sql_custom_commit_object_class.h"
#include "database_define_custom_sql_class.h"

/*
 *	帮助提示
 */
void DatabaseSqlCustom::WriteHeaderHelperText( CCodeFile& file )
{
	file->WriteWithTab(
		"/*\n"
		" * 该文件由 DatabaseCacheCustom.exe 生成，请不要随意修改。\n"
		" * 如果要调整字段信息，请修改对应的表配置文件后重新生成该文件！\n"
		" */\n");
}

/*
 *	宏开头
 */
void DatabaseSqlCustom::WriteHeaderDefineBegin( CCodeFile& file, std::string & table_name_upr )
{
	file->WriteWithTab("#ifndef %s_SQL_TBL_H\n", table_name_upr.c_str());
	file->WriteWithTab("#define %s_SQL_TBL_H\n", table_name_upr.c_str());
}

/*
 *	头文件包含
 */
void DatabaseSqlCustom::WriteHeaderInclude( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("#include \"%s_com.tbl.h\"\n", table_name.c_str());
	file->WriteWithTab("#include \"database_custom/database_sql_custom.h\"\n");
	file->WriteWithTab("#include \"dxm_util_component/util_component_sql_service_helper.h\"\n");
}

/*
 *	域开头
 */
void DatabaseSqlCustom::WriteNamespaceBegin( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("namespace %s_table {\n", table_name.c_str());
}

/*
 *	域结尾
 */
void DatabaseSqlCustom::WriteNamespaceEnd( CCodeFile& file )
{
	file->WriteWithTab("\n");
	file->WriteWithTab("};\n");
}

/*
 *	宏结尾
 */
void DatabaseSqlCustom::WriteHeaderDefineEnd( CCodeFile& file )
{
	file->WriteWithTab("\n");
	file->WriteWithTab("#endif\n");
}

/*
 *	头文件
 */
void DatabaseSqlCustom::WriteSourceInclude( CCodeFile& file, std::string & table_name )
{
	file->WriteWithTab("#include \"precompiled.h\"\n");
	file->WriteWithTab("#include \"%s_sql.tbl.h\"\n", table_name.c_str());
}

/*
 *	生成CPP文件
 */
void DatabaseSqlCustom::WriteSourceFile( const char * out_path, dios::CDatabaseTableInfo & table_info )
{
	/*
	 *	初始化变量
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
	 *	初始化变量
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
 *	生成文件
 */
void DatabaseSqlCustom::WriteFile(const char * out_path, dios::CDatabaseTableInfo & table_info) {
	WriteSourceFile(out_path, table_info);
	WriteHeaderFile(out_path, table_info);
}
