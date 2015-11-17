#include "precompiled.h"
#include "database_define_custom_record_class.h"

/*
 *	记录类开头
 */
void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassBegin( CCodeFile& file, const std::string& decl_name )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" * 表记录\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("class %s Record : public RecordLite\n", decl_name.c_str());
	file->WriteWithTab("{\n");
}

/*
 *	记录类智能指针声明
 */
void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassSharedPtr( CCodeFile& file )
{
	file->WriteWithTab("typedef boost::shared_ptr<Record> Ptr;\n");
}

/*
 *	记录类析构函数
 */
void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassDestruct( CCodeFile& file )
{
	file->WriteWithTab("virtual ~Record(void) {}\n");
}

void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassColFunction( CCodeFile& file, dios::CDatabaseTableInfo & table_info )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	获取与设置字段\n");
	file->WriteWithTab(" */\n");
	int table_col_count = table_info.GetTableColDescCount();
	for(int i=0; i<table_col_count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(i);
		if(table_col_info.type() == dios::kDatabaseColTypeBlob) {
			file->WriteWithTab("virtual void set_%s(const void* %s, int size) = 0;\n", 
				table_col_info.name().c_str(), 
				table_col_info.name().c_str());
		}
		else {
			file->WriteWithTab("virtual void set_%s(%s %s) = 0;\n", 
				table_col_info.name().c_str(), 
				c_col_type_name_read_only[table_col_info.type()],
				table_col_info.name().c_str());
		}

		
		file->WriteWithTab("virtual %s %s(void) = 0;\n", 
			c_col_type_name_read_only[table_col_info.type()],
			table_col_info.name().c_str());

		if(i != table_col_count - 1) {
			file->WriteWithTab("\n");
		}
	}
}

void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassCreateFunction( CCodeFile& file )
{
	file->WriteWithTab("/* \n");
	file->WriteWithTab(" *	新建记录\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("static Record::Ptr Create(void);\n");
}

void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassRTTI( CCodeFile& file )
{
	file->WriteWithTab("CLASS_RTTI1(Record);\n");
}

/*
 *	记录类结尾
 */
void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClassEnd( CCodeFile& file )
{
	file->WriteWithTab("};\n");
}

/*
 *	记录类
 */
void DatabaseDefineCustomRecrodClass::WriteHeaderRecordClass( CCodeFile& file, dios::CDatabaseTableInfo& table_info, const std::string& decl_name )
{
	WriteHeaderRecordClassBegin(file, decl_name);
	file->WriteWithTab("public:\n");
	file->IncreaseTab();
	WriteHeaderRecordClassSharedPtr(file);
	file->WriteWithTab("\n");
	WriteHeaderRecordClassDestruct(file);
	file->WriteWithTab("\n");
	WriteHeaderRecordClassColFunction(file, table_info);
	file->WriteWithTab("\n");
	WriteHeaderRecordClassCreateFunction(file);
	file->WriteWithTab("\n");
	WriteHeaderRecordClassRTTI(file);
	file->DecreaseTab();
	WriteHeaderRecordClassEnd(file);
}

//////////////////////////////////////////////////////////////////////////

void DatabaseDefineCustomRecrodClass::WriteSourceRecordClass( CCodeFile& file )
{
	WriteSourceRecordClassCreateFunction(file);
}

void DatabaseDefineCustomRecrodClass::WriteSourceRecordClassCreateFunction( CCodeFile& file )
{
	file->WriteWithTab("Record::Ptr Record::Create( void ) {\n");
	file->WriteWithTab("	return Record::Ptr(new RecordImpl);\n");
	file->WriteWithTab("}\n");
}
