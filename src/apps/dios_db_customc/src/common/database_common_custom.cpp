#include "precompiled.h"
#include "database_common_custom.h"

#include "boost/algorithm/string.hpp"

#include "code_file.h"

#include "database_common_custom_info_class.h"
#include "database_common_custom_record_data_class.h"
#include "database_common_custom_record_class.h"

void DatabaseCommonCustom::WriteHeaderHelperText( CCodeFile& file )
{
	file.WriteWithTab(
		"/*\n"
		" * 本文件由DatabaseCustom应用生成，请勿修改 v0.1.0\n"
		" * 调整字段信息，请先修改对应的表配置，再使用DatabaseCustom应用重新生成本文件！\n"
		" */\n");
}

void DatabaseCommonCustom::WriteHeaderDefineBegin( CCodeFile& file, const std::string& table_name_upr )
{
	file.WriteWithTab("#ifndef %s_COM_TBL_H\n", table_name_upr.c_str());
	file.WriteWithTab("#define %s_COM_TBL_H\n", table_name_upr.c_str());
}

void DatabaseCommonCustom::WriteHeaderInclude( CCodeFile& file, const std::string& table_name )
{
	file.WriteWithTab("#include \"singleton.hpp\"\n", table_name.c_str());
	file.WriteWithTab("#include \"%s_def.tbl.h\"\n", table_name.c_str());
	file.WriteWithTab("#include \"dios_db_custom/dios_db_common_custom.h\"\n");
	file.WriteWithTab("#include \"dios_db_custom/dios_db_commit_object.h\"\n");
	file.WriteWithTab("#include \"dios_util_boost/util_boost_buffer.h\"\n");
	file.WriteWithTab("#include \"dios_util_boost/util_boost_serializer.h\"\n");
}

void DatabaseCommonCustom::WriteNamespaceBegin( CCodeFile& file, const std::string& table_name )
{
	file.WriteWithTab("namespace %s_table {\n", table_name.c_str());
}

void DatabaseCommonCustom::WriteNamespaceEnd( CCodeFile& file )
{
	file.WriteWithTab("\n");
	file.WriteWithTab("};\n");
}

void DatabaseCommonCustom::WriteHeaderDefineEnd( CCodeFile& file )
{
	file.WriteWithTab("\n");
	file.WriteWithTab("#endif\n");
}

void DatabaseCommonCustom::WriteSourceInclude( CCodeFile& file, const std::string& table_name )
{
	file.WriteWithTab("#include \"precompiled.h\"\n");
	file.WriteWithTab("#include \"%s_com.tbl.h\"\n", table_name.c_str());
	file.WriteWithTab("#include \"%s_sql.tbl.h\"\n", table_name.c_str());
	file.WriteWithTab("#include \"%s_dbc.tbl.h\"\n", table_name.c_str());
}

void DatabaseCommonCustom::WriteSourceFile( const char* output_path, const dios::CDatabaseTableInfo& table_info )
{
	// 初始化变量;
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);

	std::string table_c_file = output_path;
	table_c_file.append("/");
	table_c_file.append(table_name);
	table_c_file.append("_com.tbl.cpp");

	auto table_col_count = table_info.col_info_vector().size();
	auto table_index_count = table_info.index_info_vector().size();

	auto file = CCodeFile::Create(table_c_file);
	DS_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteSourceInclude(*file, table_name);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(*file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseCommonCustomInfoClass::WriteSourceInfoClass(*file, table_info);
	file->WriteWithTab("\n");
	DatabaseCommonCustomRecordDataClass::WriteSourceRecordDataClass(*file, table_info);
	file->WriteWithTab("\n");
	DatabaseCommonCustomRecordClass::WriteSourceRecordClass(*file, table_info);
	file->DecreaseTab();
	WriteNamespaceEnd(*file);
}

void DatabaseCommonCustom::WriteHeaderFile( const char* out_path, const dios::CDatabaseTableInfo& table_info )
{
	// 初始化变量;
	std::string table_name = table_info.name();
	std::string table_name_upr = table_name;
	boost::algorithm::to_upper(table_name_upr);

	std::string table_h_file = out_path;
	table_h_file.append("/");
	table_h_file.append(table_name);
	table_h_file.append("_com.tbl.h");

	int table_col_count = table_info.col_info_vector().size();
	int table_key_count = table_info.index_info_vector().size();

	auto file = CCodeFile::Create(table_h_file);
	DS_ASSERT(file != 0, "CCodeFile::Create failed!");

	WriteHeaderHelperText(*file);
	file->WriteWithTab("\n");
	WriteHeaderDefineBegin(*file, table_name_upr);
	file->WriteWithTab("\n");
	WriteHeaderInclude(*file, table_name);
	file->WriteWithTab("\n");
	WriteNamespaceBegin(*file, table_name);
	file->IncreaseTab();
	file->WriteWithTab("\n");
	DatabaseCommonCustomInfoClass::WriteHeaderInfoClass(file, table_info);
	file->WriteWithTab("\n");
	DatabaseCommonCustomRecordDataClass::WriteHeaderRecordDataClass(file, table_info);
	file->WriteWithTab("\n");
	DatabaseCommonCustomRecordClass::WriteHeaderRecordClass(file, table_info);
	file->DecreaseTab();
	WriteNamespaceEnd(*file);
	WriteHeaderDefineEnd(*file);
}

void DatabaseCommonCustom::WriteFile(const char* out_path, const dios::CDatabaseTableInfo& table_info)
{
	WriteHeaderFile(out_path, table_info);
	WriteSourceFile(out_path, table_info);
}
