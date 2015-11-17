#include "precompiled.h"
#include "database_define_custom.h"

#include "boost/algorithm/string.hpp"
#include "dios_db_table/dios_db_tableinfo.h"

#include "code_file.h"
#include "code_helper.h"

#include "database_common_custom.h"

#include "database_define_custom_index_class.h"
#include "database_define_custom_record_class.h"
#include "database_define_custom_sql_class.h"
#include "database_define_custom_cache_class.h"

void DatabaseDefineCustom::WriteHeaderHelperText( CCodeFile& file )
{
	file.WriteWithTab(
		"/*\n"
		" * ------------------------------------------------------------------------------------\n"
		" * 本文件由DatabaseCustom应用生成，请勿修改 v0.1.0\n"
		" * 调整字段信息，请先修改对应的表配置，再使用DatabaseCustom应用重新生成本文件！\n"
		" * ------------------------------------------------------------------------------------\n"
		" * 使用说明：\n"
		" * 1.	定制代码使用环境初始化 CDatabaseCustomEnv\n"
		" * 2.	手动创建记录 tablename::Record::Create\n"
		" * 3.	创建（验证）表单 tablename::(Sql/Cache)::CreateTable\n"
		" * 4.	查询记录集 tablename::(Sql/Cache)::SelectRecordSet\n"
		" * 5.	缓存记录集 tablename::Cache::CacheRecordSet\n"
		" * 6.	释放记录集 tablename::Cache::ReleaseRecordSet\n"
		" * 7.	手动初始化记录提交对象 tablename::Record::InitCommitObject\n"
		" * 8.	提交记录 tablename::Record::Commit\n"
		" * 9.	打上删除标记 tablename::Record::set_deleted（只是标记，提交完成后才真正执行）\n"
		" * 10.	保证外部智能指针的记录全部释放\n"
		" * 11.	定制代码使用环境销毁 DatabaseSqlCustomDestroy 或者 DatabaseCacheCustomDestroy\n"
		" * ------------------------------------------------------------------------------------\n"
		" */\n");
}

/*
 *	宏开头
 */
void DatabaseDefineCustom::WriteHeaderDefineBegin( CCodeFile& file, const std::string& table_name_upr )
{
	file.WriteWithTab("#ifndef %s_DEF_TBL_H\n", table_name_upr.c_str());
	file.WriteWithTab("#define %s_DEF_TBL_H\n", table_name_upr.c_str());
}

void DatabaseDefineCustom::WriteHeaderInclude( CCodeFile& file, const std::string& table_name, const std::string& proj_name )
{
	file.WriteWithTab("#include \"database_custom/database_custom.h\"\n");
	file.WriteWithTab("#include \"%s_lib.h\"\n", proj_name.c_str());
}

void DatabaseDefineCustom::WriteHeaderDefineEnd( CCodeFile& file )
{
	file.WriteWithTab("#endif\n");
}

void DatabaseDefineCustom::WriteHeaderTableInfoMD5( CCodeFile& file, const std::string& table_name_upr, const dios::CDatabaseTableInfo& table_info )
{
	std::string md5 = table_info.CalcMD5();

	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	表单版本\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("#define %s_MD5 \"%s\";\n", table_name_upr.c_str(), md5.c_str());
}

void DatabaseDefineCustom::WriteNamespaceBegin( CCodeFile& file, const std::string& table_name )
{
	file.WriteWithTab("namespace %s_table {\n", table_name.c_str());
}

void DatabaseDefineCustom::WriteNamespaceEnd( CCodeFile& file )
{
	file.WriteWithTab("}\n");
}

void DatabaseDefineCustom::WriteHeaderFile( const char* out_path, const dios::CDatabaseTableInfo& table_info, const std::string& proj_name )
{
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);
	std::string table_h_file = out_path;
	table_h_file.append("/");
	table_h_file.append(table_name);
	table_h_file.append("_def.tbl.h");

	std::string proj_name_upr = proj_name;
	boost::algorithm::to_upper(proj_name_upr);
	std::string decl_name = proj_name_upr + "_DECL";

	auto file = CCodeFile::Create(table_h_file.c_str());
	DS_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteHeaderHelperText(*file);
	file->WriteWithTab("\n");
	WriteHeaderDefineBegin(*file, table_name_upr);
	file->WriteWithTab("\n");
	WriteHeaderInclude(*file, table_name, proj_name);
	file->WriteWithTab("\n");
	WriteHeaderTableInfoMD5(*file, table_name_upr, table_info);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(*file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseDefineCustomKeyClass::WriteHeaderKeyClass(*file, table_info, decl_name);
	file->WriteWithTab("\n");
	DatabaseDefineCustomRecrodClass::WriteHeaderRecordClass(*file, table_info, decl_name);
	file->WriteWithTab("\n");
	DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClass(*file, table_info, decl_name);
	file->WriteWithTab("\n");
	DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClass(*file, table_info, decl_name);
	file->DecreaseTab();
	WriteNamespaceEnd(*file);
	file->WriteWithTab("\n");
	WriteHeaderDefineEnd(*file);
}

void DatabaseDefineCustom::WriteSourceInclude( CCodeFile& file, const std::string& table_name )
{
	file.WriteWithTab("#include \"precompiled.h\"\n");
	file.WriteWithTab("#include \"%s_dbc.tbl.h\"\n", table_name.c_str());
	file.WriteWithTab("#include \"%s_sql.tbl.h\"\n", table_name.c_str());
}

void DatabaseDefineCustom::WriteSourceFile( const char* output_path, const dios::CDatabaseTableInfo& table_info )
{
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);
	std::string table_c_file = output_path;
	table_c_file.append("/");
	table_c_file.append(table_name);
	table_c_file.append("_def.tbl.cpp");

	auto file = CCodeFile::Create(table_c_file);
	DS_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteSourceInclude(*file, table_name);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(*file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseDefineCustomKeyClass::WriteSourceKeyClass(*file, table_info);
	file->WriteWithTab("\n");
	DatabaseDefineCustomRecrodClass::WriteSourceRecordClass(*file);
	file->DecreaseTab();
	WriteNamespaceEnd(*file);
	file->WriteWithTab("\n");
}

void DatabaseDefineCustom::WriteFile( const char* output_path, const dios::CDatabaseTableInfo& table_info, const std::string& proj_name )
{
	WriteHeaderFile(output_path, table_info, proj_name);
	WriteSourceFile(output_path, table_info);
}