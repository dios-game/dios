#include "precompiled.h"
#include  "database_sql_custom_commit_object_class.h"

#include "code_file.h"
#include "code_helper.h"

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassBegin( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 表记录\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class DatabaseSqlCommitObject : public CommitObject\n");
	file.WriteWithTab("{\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("DatabaseSqlCommitObject(const std::string& dest_id, CommitStatus commit_status, RecordData* record_data);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("~DatabaseSqlCommitObject(void);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassCommitInsertFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	插入提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void CommitInsert(boost::function<void(bool)> func);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassCommitUpdateFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	更新提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void CommitUpdate(boost::function<void(bool)> func);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassCommitDeleteFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	删除提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void CommitDelete(boost::function<void(bool)> func);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassSetRecordIDFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	设置记录编号函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void SetRecordID(uint32 record_id);\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassMember( CCodeFile& file )
{
	file.WriteWithTab("BaseDatabaseSqlCommitTool commit_tool_;\n");
	file.WriteWithTab("std::string dest_id_;\n");
	file.WriteWithTab("RecordData *record_data_;\n");
	file.WriteWithTab("boost::shared_ptr<uint32> record_id_;\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteHeaderCommitObjectClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteHeaderCommitObjectClassBegin(file);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();
	WriteHeaderCommitObjectClassStruct(file, table_info);
	WriteHeaderCommitObjectClassDestruct(file);
	file.WriteWithTab("\n");
	WriteHeaderCommitObjectClassCommitInsertFunction(file);
	WriteHeaderCommitObjectClassCommitUpdateFunction(file);
	WriteHeaderCommitObjectClassCommitDeleteFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderCommitObjectClassSetRecordIDFunction(file);
	file.DecreaseTab();
	file.WriteWithTab("protected:\n");
	file.IncreaseTab();
	WriteHeaderCommitObjectClassMember(file);
	file.DecreaseTab();
	WriteHeaderCommitObjectClassEnd(file);
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("DatabaseSqlCommitObject::DatabaseSqlCommitObject( const std::string& dest_id, CommitStatus commit_status, RecordData* record_data ) : record_id_(new uint32(0)) {\n");
	file.WriteWithTab("	dest_id_ = dest_id;\n");
	file.WriteWithTab("	record_data_ = record_data;\n");
	file.WriteWithTab("	commit_status_ = commit_status;\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("DatabaseSqlCommitObject::~DatabaseSqlCommitObject( void ) {\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassCommitInsertFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	插入提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void DatabaseSqlCommitObject::CommitInsert( boost::function<void(bool)> func ) {\n");
	file.WriteWithTab("	BaseDatabaseSqlCommitRecord::Ptr commit_record(new DatabaseSqlCommitRecord(record_id_, *record_data_));\n");
	file.WriteWithTab("	commit_tool_.CommitInsert(dest_id_, commit_record, func);\n");
	file.WriteWithTab("	record_data_->clear_record_dirty();\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassCommitUpdateFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	更新提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void DatabaseSqlCommitObject::CommitUpdate( boost::function<void(bool)> func ) {\n");
	file.WriteWithTab("	BaseDatabaseSqlCommitRecord::Ptr commit_record(new DatabaseSqlCommitRecord(record_id_, *record_data_));\n");
	file.WriteWithTab("	commit_tool_.CommitUpdate(dest_id_, commit_record, func);\n");
	file.WriteWithTab("	record_data_->clear_record_dirty();\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassCommitDeleteFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	删除提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void DatabaseSqlCommitObject::CommitDelete( boost::function<void(bool)> func ) {\n");
	file.WriteWithTab("	BaseDatabaseSqlCommitRecord::Ptr commit_record(new DatabaseSqlCommitRecord(record_id_, *record_data_));\n");
	file.WriteWithTab("	commit_tool_.CommitDelete(dest_id_, commit_record, func);\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClassSetRecordIDFunction( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	设置记录编号函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void DatabaseSqlCommitObject::SetRecordID( uint32 record_id ) {\n");
	file.WriteWithTab("	if(record_id_) {\n");
	file.WriteWithTab("		*record_id_ = record_id;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitObjectClass::WriteSourceCommitObjectClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteSourceCommitObjectClassStruct(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceCommitObjectClassDestruct(file);
	file.WriteWithTab("\n");
	WriteSourceCommitObjectClassCommitInsertFunction(file);
	file.WriteWithTab("\n");
	WriteSourceCommitObjectClassCommitUpdateFunction(file);
	file.WriteWithTab("\n");
	WriteSourceCommitObjectClassCommitDeleteFunction(file);
	file.WriteWithTab("\n");
	WriteSourceCommitObjectClassSetRecordIDFunction(file);
}

