#include "precompiled.h"
#include "database_common_custom_info_class.h"

#include "code_file.h"
#include "code_helper.h"

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassBegin( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	����Ϣ\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class Info : public BaseDatabaseInfo\n");
	file.WriteWithTab("{\n");
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassSetupTableInfoFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	���TableInfo����\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void SetupTableInfo(dios::CDatabaseTableInfo& table_info);\n");
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassGetTableNameFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * ��ñ�����\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline const char* GetTableName(void) { return \"%s\"; }\n", table_info.name().c_str());
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassColCountFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * ��ñ��ֶ�����\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("inline uint GetColCount(void) { return %u; }\n", table_info.col_info_vector().size());
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassSingleton( CCodeFile& file )
{
	file.WriteWithTab("EAGER_SINGLETON_H(Info);\n");
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseCommonCustomInfoClass::WriteHeaderInfoClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	// ����Ϣ�࿪ͷ;
	WriteHeaderInfoClassBegin(file);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();

	// ����Ϣ����;
	WriteHeaderInfoClassSetupTableInfoFunction(file, table_info);
	file.WriteWithTab("\n");

	// ��¼��ı�����;
	WriteHeaderInfoClassGetTableNameFunction(file, table_info);
	file.WriteWithTab("\n");

	// ��¼����ֶ�����;
	WriteHeaderInfoClassColCountFunction(file, table_info);
	file.WriteWithTab("\n");

	// ��������;
	WriteHeaderInfoClassSingleton(file);

	// ����Ϣ���β;
	file.DecreaseTab();
	WriteHeaderInfoClassEnd(file);
}

void DatabaseCommonCustomInfoClass::WriteSourceInfoClassSetupTableInfoFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * ���TableInfo����\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void Info::SetupTableInfo( dios::CDatabaseTableInfo& table_info ) {\n");
	file.WriteWithTab("	table_info.set_table_name(\"%s\");\n", table_info.name().c_str());
	file.WriteWithTab("\n");

	for(ds_int32 i=0; i<table_info.col_info_vector().size(); ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		file.WriteWithTab("	table_info.AddTableColDesc(\"%s\", %s, %u);\n", 
			table_col_info.name().c_str(), 
			sCodeHelper->GetColTypeEnumName(table_col_info.type()),
			table_col_info.char_size());
	}
	file.WriteWithTab("\n");

	for(ds_int32 i=0; i<table_info.index_info_vector().size(); ++i)
	{
		auto table_index_info = table_info.index_info_vector()[i];
		file.WriteWithTab("	tableinfo_project::TableKeyCol %s_key_col;\n", table_index_info.name().c_str());
		file.WriteWithTab("	%s_key_col.count = %u;\n", 
			table_index_info.name().c_str(), 
			table_index_info.col_name_array().size());

		for(int j=0; j<table_index_info.col_name_array().size(); ++j)
		{
			file.WriteWithTab("	%s_key_col.value[%d] = %d;\n", 
				table_index_info.name().c_str(), 
				j, 
				table_index_info.col_name_array()[j]);
		}
		file.WriteWithTab("	table_info.AddTableKeyDesc(\"%s\", %s_key_col, %s);\n", 
			table_index_info.name().c_str(), 
			table_index_info.name().c_str(),
			table_index_info.is_primary_key() ? "true" : "false");
		if(i != table_info.index_info_vector().size()-1) {
			file.WriteWithTab("\n");
		}
	}
	file.WriteWithTab("}\n");
}

void DatabaseCommonCustomInfoClass::WriteSourceInfoClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	// ����Ϣ����;
	WriteSourceInfoClassSetupTableInfoFunction(file, table_info);
	file.WriteWithTab("\n");
}