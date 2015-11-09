#include "precompiled.h"
#include "database_define_custom_key_class.h"

/*
 *	索引类开头
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClassBegin( CCodeFile& file, 
	const char* table_key_name, 
	std::string& upper_table_key_name,
	const std::string& decl_name )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	索引 %s\n", table_key_name);
	file->WriteWithTab(" */\n");
	file->WriteWithTab("class %s KEY_%s\n", decl_name.c_str(), upper_table_key_name.c_str());
	file->WriteWithTab("{\n");
}

/*
 *	索引类构造函数
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClassStruct( CCodeFile& file, std::string & upper_table_key_name, tableinfo_project::TableKeyDesc * table_index_info, dios::CDatabaseTableInfo & table_info )
{
	file->WriteWithTab("KEY_%s(void);\n", upper_table_key_name.c_str());
	file->WriteWithTab("KEY_%s(", upper_table_key_name.c_str());
	for(int i=0; i<table_index_info->key_col.count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(table_index_info->key_col.value[i]);
		file->Write("%s %s", c_col_type_name_read_only[table_col_info.type()], table_col_info.name().c_str());
		if(i != (table_index_info->key_col.count-1)) {
			file->Write(", ");
		}
	}
	file->Write(");\n");
}

/*
 *	索引类析构函数
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClassDestruct( CCodeFile& file, std::string & upper_table_key_name )
{
	file->WriteWithTab("~KEY_%s(void);\n", upper_table_key_name.c_str());
}

/*
 *	索引类私有变量
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClassMember( CCodeFile& file, tableinfo_project::TableKeyDesc * table_index_info, dios::CDatabaseTableInfo & table_info )
{
	for(int i=0; i<table_index_info->key_col.count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(table_index_info->key_col.value[i]);
		file->WriteWithTab("%s %s_;\n", c_col_type_name[table_col_info.type()], table_col_info.name().c_str());
	}
}

/*
 *	索引类结束
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClassEnd( CCodeFile& file )
{
	file->WriteWithTab("};\n");
}

/*
 *	索引类
 */
void DatabaseDefineCustomKeyClass::WriteHeaderKeyClass( CCodeFile& file, dios::CDatabaseTableInfo & table_info, const std::string& decl_name )
{
	/*
	 *	索引类
	 */
	int table_key_count = table_info.GetTableKeyDescCount();
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);

		WriteHeaderKeyClassBegin(file, table_index_info->index_name, upper_table_key_name, decl_name);
		file->WriteWithTab("public:\n");
		file->IncreaseTab();
		WriteHeaderKeyClassStruct(file, upper_table_key_name, table_index_info, table_info);
		WriteHeaderKeyClassDestruct(file, upper_table_key_name);
		file->WriteWithTab("\n");
		WriteHeaderKeyClassMember(file, table_index_info, table_info);
		file->DecreaseTab();
		WriteHeaderKeyClassEnd(file);

		if(i != table_key_count - 1) {
			file->WriteWithTab("\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void DatabaseDefineCustomKeyClass::WriteSourceKeyClassStruct( CCodeFile& file, std::string & upper_table_key_name, tableinfo_project::TableKeyDesc * table_index_info, dios::CDatabaseTableInfo & table_info )
{
	file->WriteWithTab("KEY_%s::KEY_%s( void ) {\n", upper_table_key_name.c_str(), upper_table_key_name.c_str());
	for(int i=0; i<table_index_info->key_col.count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(table_index_info->key_col.value[i]);
		const char * init = GetRecordStructColInitString(table_col_info);
		if(init) {
			file->Write("%s\n", init);
		}
	}
	file->WriteWithTab("}\n");
	file->WriteWithTab("\n");

	file->WriteWithTab("KEY_%s::KEY_%s( ", upper_table_key_name.c_str(), upper_table_key_name.c_str());
	for(int i=0; i<table_index_info->key_col.count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(table_index_info->key_col.value[i]);
		file->Write("%s %s", c_col_type_name_read_only[table_col_info.type()], table_col_info.name().c_str());
		if(i != (table_index_info->key_col.count-1)) {
			file->Write(", ");
		}
	}
	file->Write(" ) {\n");
	for(int i=0; i<table_index_info->key_col.count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(table_index_info->key_col.value[i]);
		file->WriteWithTab("	%s_ = %s;\n", table_col_info.name().c_str(), table_col_info.name().c_str());
	}
	file->WriteWithTab("}\n");
}

void DatabaseDefineCustomKeyClass::WriteSourceKeyClassDestruct( CCodeFile& file, std::string & upper_table_key_name )
{
	file->WriteWithTab("KEY_%s::~KEY_%s( void ) {\n", upper_table_key_name.c_str(), upper_table_key_name.c_str());
	file->WriteWithTab("}\n");
}

void DatabaseDefineCustomKeyClass::WriteSourceKeyClass( CCodeFile& file, dios::CDatabaseTableInfo& table_info )
{
	/*
	 *	索引类
	 */
	int table_key_count = table_info.GetTableKeyDescCount();
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);

		WriteSourceKeyClassStruct(file, upper_table_key_name, table_index_info, table_info);
		file->WriteWithTab("\n");
		WriteSourceKeyClassDestruct(file, upper_table_key_name);

		if(i != table_key_count - 1) {
			file->WriteWithTab("\n");
		}
	}
}