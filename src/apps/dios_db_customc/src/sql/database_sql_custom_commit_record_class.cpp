#include "precompiled.h"
#include "database_sql_custom_commit_record_class.h"

#include "dios_db_table/dios_db_tableinfo.h"

#include "code_file.h"
#include "code_helper.h"

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassBegin( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 表记录;\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class DatabaseSqlCommitRecord : public BaseDatabaseSqlCommitRecord\n");
	file.WriteWithTab("{\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("DatabaseSqlCommitRecord(void);\n");
	file.WriteWithTab("DatabaseSqlCommitRecord(boost::shared_ptr<uint32> record_id, const RecordData& record_data);\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("~DatabaseSqlCommitRecord(void);\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassIsDirtyFunction( CCodeFile& file )
{
	file.WriteWithTab("// 是否为脏数据;\n");
	file.WriteWithTab("inline bool IsDirty(void) { return record_data_.record_dirty(); }\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassCommitInsertFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("// 提交插入记录函数;\n");
	file.WriteWithTab("bool CommitInsert(Foundation::SqlService::ISqlConnector::Ptr sql_connector);\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassCommitUpdateFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("// 提交更新记录函数;\n");
	file.WriteWithTab("bool CommitUpdate(Foundation::SqlService::ISqlConnector::Ptr sql_connector);\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassCommitDeleteFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("// 提交删除记录函数;\n");
	file.WriteWithTab("bool CommitDelete(Foundation::SqlService::ISqlConnector::Ptr sql_connector);\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassProtectedMember( CCodeFile& file )
{
	file.WriteWithTab("RecordData record_data_;\n");
	file.WriteWithTab("boost::shared_ptr<uint32> record_id_;\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteHeaderCommitRecordClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteHeaderCommitRecordClassBegin(file);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();
	WriteHeaderCommitRecordClassStruct(file, table_info);
	WriteHeaderCommitRecordClassDestruct(file);
	file.WriteWithTab("\n");
	WriteHeaderCommitRecordClassIsDirtyFunction(file);
	file.WriteWithTab("\n");
	WriteHeaderCommitRecordClassCommitInsertFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderCommitRecordClassCommitUpdateFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteHeaderCommitRecordClassCommitDeleteFunction(file, table_info);
	file.DecreaseTab();

	file.WriteWithTab("protected:\n");
	file.IncreaseTab();
	WriteHeaderCommitRecordClassProtectedMember(file);
	file.DecreaseTab();
	WriteHeaderCommitRecordClassEnd(file);
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClassStruct( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("DatabaseSqlCommitRecord::DatabaseSqlCommitRecord( void ) {\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");
	file.WriteWithTab("DatabaseSqlCommitRecord::DatabaseSqlCommitRecord( boost::shared_ptr<uint32> record_id, const RecordData& record_data ) : record_data_(record_data),\n");
	file.WriteWithTab("record_id_(record_id) {\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClassDestruct( CCodeFile& file )
{
	file.WriteWithTab("DatabaseSqlCommitRecord::~DatabaseSqlCommitRecord( void ) {\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClassCommitInsertFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	char prepare_code[4096]; prepare_code[0] = 0;
	char col_name_code[4096]; col_name_code[0] = 0;
	char col_format_code[4096]; col_format_code[0] = 0;
	char col_value_code[4096]; col_value_code[0] = 0;
	char blob_code[8192]; blob_code[0] = 0;
	
	auto col_count = table_info.col_info_vector().size();
	for(int i=0; i<col_count; ++i)
	{
		auto table_col_info = table_info.col_info_vector()[i];
		sprintf(col_name_code+strlen(col_name_code), "%s, ", table_col_info.name().c_str());

		switch(table_col_info.type())
		{
		case dios::kDatabaseColTypeSmallInt: 
			{ 
				sprintf(col_format_code+strlen(col_format_code), "%%hd, ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedSmallInt:
			{ 
				sprintf(col_format_code+strlen(col_format_code), "%%hu, ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeInt: 
			{ 
				sprintf(col_format_code+strlen(col_format_code), "%%d, ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedInt:
			{
				sprintf(col_format_code+strlen(col_format_code), "%%u, ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str()); 
			}
			break;
		case dios::kDatabaseColTypeFloat: 
			{ 
				sprintf(col_format_code+strlen(col_format_code), "%%f, "); 
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str()); 
			}
			break;
		case dios::kDatabaseColTypeString: 
			{ 
				sprintf(col_format_code+strlen(col_format_code), "'%%s', ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s().c_str(), ", table_col_info.name().c_str()); 
			}
			break;
		case dios::kDatabaseColTypeBlob: 
			{ 
				sprintf(col_format_code+strlen(col_format_code), "?, ");
				sprintf(blob_code+strlen(blob_code), 
					"%s	sql_connector->ExecuteSqlPushParam(Foundation::SqlService::SQL_PARAM_TYPE_BLOB, (void*)record_data_.%s().data(), record_data_.%s().size());\n",
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUuid:
			{
				sprintf(prepare_code+strlen(prepare_code), "%s	std::string %s_u2s = to_string(record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
				sprintf(col_format_code+strlen(col_format_code), "'%%s', ");
				sprintf(col_value_code+strlen(col_value_code), "%s_u2s.c_str(), ", table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeChar:
			{ 
				sprintf(col_format_code+strlen(col_format_code), "%%c, ");
				sprintf(col_value_code+strlen(col_value_code), "record_data_.%s(), ", table_col_info.name().c_str());
			}
			break;
		}
	}

	if(col_name_code[0] != 0) {
		col_name_code[strlen(col_name_code) - 2] = 0;
	}
	if(col_format_code[0] != 0) {
		col_format_code[strlen(col_format_code) - 2] = 0;
	}
	if(col_value_code[0] != 0) {
		col_value_code[strlen(col_value_code) - 2] = 0;
	}

	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 提交插入记录函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool DatabaseSqlCommitRecord::CommitInsert( Foundation::SqlService::ISqlConnector::Ptr sql_connector ) {\n");
	file.WriteWithTab("	char sql[4096];\n");
	file.WriteWithTab("	bool is_successful = false;\n");
	file.Write("%s", prepare_code);
	file.WriteWithTab("\n");
	file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
	file.WriteWithTab("	sprintf(sql, \"insert into %s (%s) values (%s);\", %s);\n", table_info.name().c_str(), col_name_code, col_format_code, col_value_code);
	file.WriteWithTab("	sql_connector->ExecuteSqlBegin(sql);\n");
	file.Write("%s", blob_code);
	file.WriteWithTab("	sql_connector->ExecuteSqlEnd(sql_query_error);\n");
	file.WriteWithTab("	is_successful = (sql_query_error == Foundation::SqlService::SQL_QUERY_ERROR_OK);\n");
	file.WriteWithTab("	if(is_successful && record_id_) {\n");
	file.WriteWithTab("		*record_id_ = sql_connector->GetAutoIncrementID();\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	return is_successful;\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClassCommitUpdateFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	char prepare_code[1024]; prepare_code[0] = 0;
	char code[10240]; code[0] = 0;

	int col_count = table_info.col_info_vector().size();
	for(int i=0; i<col_count; ++i)
	{
		sprintf(code+strlen(code), "%s	if(record_data_.col_dirty(%d)) {\n", file.tab_string().c_str(), i);

		auto table_col_info = table_info.col_info_vector()[i];
		switch(table_col_info.type())
		{
		case dios::kDatabaseColTypeSmallInt: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%hd, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedSmallInt: 
			{ 
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%hu, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeInt: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%d, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedInt:
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%u, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeFloat: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%f, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeString: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s='%%s', \", record_data_.%s().c_str());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeBlob: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=?, \");\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str());
				sprintf(code+strlen(code), "%s		blob_list.push_back(record_data_.%s());\n", 
					file.tab_string().c_str(),
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUuid:
			{
				sprintf(prepare_code+strlen(prepare_code), "%s	std::string %s_u2s = to_string(record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s='%%s', \", %s_u2s.c_str());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(),
					table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeChar: 
			{
				sprintf(code+strlen(code), "%s		sprintf(sql+strlen(sql), \"%s=%%c, \", record_data_.%s());\n", 
					file.tab_string().c_str(), 
					table_col_info.name().c_str(), 
					table_col_info.name().c_str());
			}
			break;
		}

		sprintf(code+strlen(code), "%s	}\n", file.tab_string().c_str());
	}
	sprintf(code+strlen(code), "%s	sprintf(sql+strlen(sql)-strlen(\", \"), \" where id=%%u;\", record_id_ ? *record_id_ : 0);", file.tab_string().c_str());

	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 提交更新记录函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool DatabaseSqlCommitRecord::CommitUpdate( Foundation::SqlService::ISqlConnector::Ptr sql_connector ) {\n");
	file.WriteWithTab("	char sql[4096];\n");
	file.WriteWithTab("	std::list<std::string> blob_list;\n");
	file.Write("%s", prepare_code);
	file.WriteWithTab("\n");
	file.WriteWithTab("	sprintf(sql, \"update %s set \");\n", table_info.name().c_str());
	file.Write("%s", code);
	file.WriteWithTab("\n");
	file.WriteWithTab("	\n");
	file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
	file.WriteWithTab("	sql_connector->ExecuteSqlBegin(sql);\n");
	file.WriteWithTab("	std::list<std::string>::iterator itor = blob_list.begin();\n");
	file.WriteWithTab("	while(itor != blob_list.end())\n");
	file.WriteWithTab("	{\n");
	file.WriteWithTab("		sql_connector->ExecuteSqlPushParam(Foundation::SqlService::SQL_PARAM_TYPE_BLOB, (void*)(*itor).data(), (*itor).size());\n");
	file.WriteWithTab("		++itor;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	sql_connector->ExecuteSqlEnd(sql_query_error);\n");
	file.WriteWithTab("	return (sql_query_error == Foundation::SqlService::SQL_QUERY_ERROR_OK);\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClassCommitDeleteFunction( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	char prepare_code[1024]; prepare_code[0] = 0;
	char code[10240]; code[0] = 0;

	file.WriteWithTab("/*\n");
	file.WriteWithTab(" * 提交删除记录函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("bool DatabaseSqlCommitRecord::CommitDelete( Foundation::SqlService::ISqlConnector::Ptr sql_connector ) {\n");
	file.WriteWithTab("	char sql[4096];\n");
	file.WriteWithTab("	std::list<std::string> blob_list;\n");
	file.Write("%s\n", prepare_code);
	file.Write("%s\n", code);
	file.WriteWithTab("	sprintf(sql, \"delete from %s where id=%%u;\", record_id_ ? *record_id_ : 0);\n", table_info.name().c_str());
	file.WriteWithTab("	\n");
	file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
	file.WriteWithTab("	sql_connector->ExecuteSqlBegin(sql);\n");
	file.WriteWithTab("	std::list<std::string>::iterator itor = blob_list.begin();\n");
	file.WriteWithTab("	while(itor != blob_list.end())\n");
	file.WriteWithTab("	{\n");
	file.WriteWithTab("		sql_connector->ExecuteSqlPushParam(Foundation::SqlService::SQL_PARAM_TYPE_BLOB, (void*)(*itor).data(), (*itor).size());\n");
	file.WriteWithTab("		++itor;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	sql_connector->ExecuteSqlEnd(sql_query_error);\n");
	file.WriteWithTab("	return (sql_query_error == Foundation::SqlService::SQL_QUERY_ERROR_OK);\n");
	file.WriteWithTab("}\n");
}

void DatabaseSqlCustomCommitRecordClass::WriteSourceCommitRecordClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteSourceCommitRecordClassStruct(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceCommitRecordClassDestruct(file);
	file.WriteWithTab("\n");
	WriteSourceCommitRecordClassCommitInsertFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceCommitRecordClassCommitUpdateFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceCommitRecordClassCommitDeleteFunction(file, table_info);
}

