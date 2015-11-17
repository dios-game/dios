#include "precompiled.h"
#include "database_define_custom_sql_class.h"

#include "boost/algorithm/string.hpp"

#include "code_file.h"
#include "code_helper.h"

void DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClassBegin( CCodeFile& file, const std::string& decl_name )
{
	file.WriteWithTab("/* \n");
	file.WriteWithTab(" *	SQL操作类\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("class %s Sql\n", decl_name.c_str());
	file.WriteWithTab("{\n");
}

void DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClassEnd( CCodeFile& file )
{
	file.WriteWithTab("};\n");
}

void DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClassCreateTable( CCodeFile& file )
{
	file.WriteWithTab("static void CreateTable(const std::string& dest_id, boost::function<void(bool)> func);\n");
}

void DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClassSelectRecordSet( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("static void SelectRecordSet(const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func);\n");
	file.WriteWithTab("static void SelectRecordSet(const std::string& dest_id, const std::string& search_str, boost::function<void(const std::list<Record::Ptr>&)> func);\n");
	int table_key_count = table_info.index_info_vector().size();
	for(int i=0; i<table_key_count; ++i)
	{
		auto table_index_info = table_info.index_info_vector()[i];
		std::string upper_table_key_name = table_index_info.name();
		boost::algorithm::to_upper(upper_table_key_name);
		file.WriteWithTab("static void SelectRecordSet(const std::string& dest_id, const KEY_%s& key, boost::function<void(const std::list<Record::Ptr>&)> func);\n", upper_table_key_name.c_str());
	}
}

void DatabaseDefineCustomSqlClass::WriteHeaderDatabaseSqlClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info, const std::string& decl_name )
{
	WriteHeaderDatabaseSqlClassBegin(file, decl_name);
	file.WriteWithTab("public:\n");
	file.IncreaseTab();
	WriteHeaderDatabaseSqlClassCreateTable(file);
	WriteHeaderDatabaseSqlClassSelectRecordSet(file, table_info);
	file.DecreaseTab();
	WriteHeaderDatabaseSqlClassEnd(file);
}

void DatabaseDefineCustomSqlClass::WriteSourceDatabaseSqlClass( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	WriteSourceParseFromSqlFunction(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceSelectResult2Record(file);
	file.WriteWithTab("\n");
	WriteSourceCommitSelectRecordSet(file, table_info);
	file.WriteWithTab("\n");
	WriteSourceCreateTable(file);
	file.WriteWithTab("\n");
	WriteSourceSelectRecordSet(file, table_info);
}

void DatabaseDefineCustomSqlClass::WriteSourceCreateTable( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	建表操作\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void Sql::CreateTable( const std::string& dest_id, boost::function<void(bool)> func ) {\n");
	file.WriteWithTab("	BaseDatabaseSqlCreateTable(dest_id, Info::GetInstancePtr(), func);\n");
	file.WriteWithTab("}\n");
}

void DatabaseDefineCustomSqlClass::WriteSourceSelectResult2Record( CCodeFile& file )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	查询结果转换为新建记录\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("static void SelectResult2Record( Foundation::SqlService::ISqlResult::Ptr& sql_result, std::string dest_id, boost::function<void(const std::list<Record::Ptr>&)>& func ) {\n");
	file.WriteWithTab("	if(!func) {\n");
	file.WriteWithTab("		return;\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	std::list<Record::Ptr> record_list;\n");
	file.WriteWithTab("	if(sql_result) {\n");
	file.WriteWithTab("		while(sql_result->FetchRow()) {\n");
	file.WriteWithTab("			\n");
	file.WriteWithTab("			RecordImpl::Ptr record(new RecordImpl);\n");
	file.WriteWithTab("			record->InitCommitObject(kDatabaseSqlCustom, dest_id.c_str(), kCommitStatusUpdate);\n");
	file.WriteWithTab("			DatabaseSqlCommitObject *sql_commit_object = dynamic_cast<DatabaseSqlCommitObject*>(record->commit_object());\n");
	file.WriteWithTab("			if(sql_commit_object) {\n");
	file.WriteWithTab("				sql_commit_object->SetRecordID(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"id\"));\n");
	file.WriteWithTab("			}\n");
	file.WriteWithTab("			ParseFromSql(sql_result, record->record_data());\n");
	file.WriteWithTab("			record->record_data().clear_record_dirty();\n");
	file.WriteWithTab("			record_list.push_back(record);\n");
	file.WriteWithTab("		}\n");
	file.WriteWithTab("	}\n");
	file.WriteWithTab("	func(record_list);\n");
	file.WriteWithTab("}\n");
}

void DatabaseDefineCustomSqlClass::WriteSourceCommitSelectRecordSet( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	查询结果提交函数\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("static void CommitSelectRecordSet( Foundation::SqlService::ISqlConnector::Ptr sql_connector, const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n");
	file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
	file.WriteWithTab("	Foundation::SqlService::ISqlResult::Ptr sql_result = sql_connector->ExecuteSql(\"select * from %s\", sql_query_error);\n", table_info.name().c_str());
	file.WriteWithTab("	SelectResult2Record(sql_result, dest_id, func);\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");

	file.WriteWithTab("static void CommitSelectRecordSet( Foundation::SqlService::ISqlConnector::Ptr sql_connector, const std::string& search_str, const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n");
	file.WriteWithTab("	char sql[4096];\n");
	file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
	file.WriteWithTab("	sprintf(sql, \"select * from %s where %%s\", search_str.c_str());\n", table_info.name().c_str());
	file.WriteWithTab("	Foundation::SqlService::ISqlResult::Ptr sql_result = sql_connector->ExecuteSql(sql, sql_query_error);\n");
	file.WriteWithTab("	SelectResult2Record(sql_result, dest_id, func);\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");

	int table_key_count = table_info.index_info_vector().size();
	if(table_key_count <= 0) {
		return;
	}
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	查询结果提交函数\n");
	file.WriteWithTab(" */\n");
	for(int i=0; i<table_key_count; ++i)
	{
		auto table_index_info = table_info.index_info_vector()[i];
		std::string upper_table_key_name = table_index_info.name().c_str();
		boost::algorithm::to_upper(upper_table_key_name);

		char prepare_code[1024]; prepare_code[0] = 0;
		char where_code[1024]; where_code[0] = 0;
		char value_code[1024]; value_code[0] = 0;
		char blob_code[1024]; blob_code[0] = 0;

		int j = 0;
		for(; j<table_index_info.col_name_array().size(); ++j)
		{
			auto table_col_info = table_info.GetTableColDesc(table_index_info.col_name_array()[j]);
			
			switch(table_col_info.type())
			{
			case dios::kDatabaseColTypeSmallInt: 
				{
					sprintf(where_code+strlen(where_code), "%s=%%hd and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeUnsignedSmallInt: 
				{
					sprintf(where_code+strlen(where_code), "%s=%%hu and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeInt: 
				{
					sprintf(where_code+strlen(where_code), "%s=%%d and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeUnsignedInt:
				{
					sprintf(where_code+strlen(where_code), "%s=%%u and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeFloat: 
				{
					sprintf(where_code+strlen(where_code), "%s=%%f and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeString: 
				{
					sprintf(where_code+strlen(where_code), "%s='%%s' and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_.c_str(), ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeBlob: 
				{
					break;
				}
				break;
			case dios::kDatabaseColTypeUuid:
				{
					sprintf(prepare_code+strlen(prepare_code), "		std::string %s_u2s = to_string(key.%s_);\n", table_col_info.name().c_str(), table_col_info.name().c_str());
					sprintf(where_code+strlen(where_code), "%s='%%s' and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "%s_u2s.c_str(), ", table_col_info.name().c_str());
				}
				break;
			case dios::kDatabaseColTypeChar: 
				{
					sprintf(where_code+strlen(where_code), "%s=%%c and ", table_col_info.name().c_str());
					sprintf(value_code+strlen(value_code), "key.%s_, ", table_col_info.name().c_str());
				}
				break;
			}
		}
		if(j != table_index_info->key_col.count) {
			continue;
		}

		file.WriteWithTab("static void CommitSelectRecordSet( Foundation::SqlService::ISqlConnector::Ptr sql_connector, const KEY_%s& key, const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n", 
			upper_table_key_name.c_str());
		file.WriteWithTab("	char sql[4096];\n");
		file.WriteWithTab("%s\n", prepare_code);
		where_code[strlen(where_code)-strlen(" and ")] = 0;
		value_code[strlen(value_code)-strlen(", ")] = 0;
		file.WriteWithTab("	Foundation::SqlService::eSqlQueryError sql_query_error = Foundation::SqlService::SQL_QUERY_ERROR_OK;\n");
		file.WriteWithTab("	sprintf(sql, \"select * from %s where %s\", %s);\n", table_info.name().c_str(), where_code, value_code);
		file.WriteWithTab("	Foundation::SqlService::ISqlResult::Ptr sql_result = sql_connector->ExecuteSql(sql, sql_query_error);\n", table_info.name().c_str());
		file.WriteWithTab("	SelectResult2Record(sql_result, dest_id, func);\n");
		file.WriteWithTab("}\n");

		if(i != table_key_count - 1) {
			file.WriteWithTab("\n");
		}
	}
}

/*
 *	查询函数
 */
void DatabaseDefineCustomSqlClass::WriteSourceSelectRecordSet( CCodeFile& file, dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	查询整表操作（当DatabaseSqlRecord为空时，表示查询结束）\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("void Sql::SelectRecordSet( const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n");
	file.WriteWithTab("	std::string temp_dest_id(dest_id);\n");
 	file.WriteWithTab("	BaseDatabaseSqlSelectRecordSet(dest_id, boost::bind(CommitSelectRecordSet, _1, temp_dest_id, func));\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");

	file.WriteWithTab("void Sql::SelectRecordSet( const std::string& dest_id, const std::string& search_str, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n");
	file.WriteWithTab("	void (*temp_func)(Foundation::SqlService::ISqlConnector::Ptr, const std::string&, const std::string&, boost::function<void(const std::list<Record::Ptr>&)>) = CommitSelectRecordSet;\n");
	file.WriteWithTab("	std::string temp_dest_id(dest_id);\n");
	file.WriteWithTab("	BaseDatabaseSqlSelectRecordSet(dest_id, boost::bind(temp_func, _1, search_str, temp_dest_id, func));\n");
	file.WriteWithTab("}\n");
	file.WriteWithTab("\n");

	int table_key_count = table_info.GetTableKeyDescCount();
	if(table_key_count > 0) {
		file.WriteWithTab("/*\n");
		file.WriteWithTab(" *	根据索引查询操作（当DatabaseSqlRecord为空时，表示查询结束）\n");
		file.WriteWithTab(" */\n");
	}
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info.name().c_str();
		boost::algorithm::to_upper(upper_table_key_name);

		file.WriteWithTab("void Sql::SelectRecordSet( const std::string& dest_id, const KEY_%s& key, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n", upper_table_key_name.c_str());
		file.WriteWithTab("	void (*temp_func)(Foundation::SqlService::ISqlConnector::Ptr, const KEY_%s&, const std::string&, boost::function<void(const std::list<Record::Ptr>&)>) = CommitSelectRecordSet;\n", upper_table_key_name.c_str());
 		file.WriteWithTab("	std::string temp_dest_id(dest_id);\n");
		file.WriteWithTab("	BaseDatabaseSqlSelectRecordSet(dest_id, boost::bind(temp_func, _1, key, temp_dest_id, func));\n");
		file.WriteWithTab("}\n");

		if(i != table_key_count-1) {
			file.WriteWithTab("\n");
		}
	}
}

/*
 *	记录类从SQL加载
 */
void DatabaseDefineCustomSqlClass::WriteSourceParseFromSqlFunction( CCodeFile& file, dios::CDatabaseTableInfo & table_info )
{
	file.WriteWithTab("/*\n");
	file.WriteWithTab(" *	记录类从SQL加载\n");
	file.WriteWithTab(" */\n");
	file.WriteWithTab("static void ParseFromSql( Foundation::SqlService::ISqlResult::Ptr& sql_result, RecordData& record_data ) {\n");
	int table_col_count = table_info.GetTableColDescCount();
	for(int i=0; i<table_col_count; ++i)
	{
		tableinfo_project::TableColDesc * table_col_info = table_info.GetTableColDesc(i);

		switch(table_col_info.type())
		{
		case tableinfo_project::RECORD_COL_TYPE_SMALL_INT:
			{
				file.WriteWithTab("	record_data.set_%s(static_cast<short>(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"%s\")));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedSmallInt:
			{
				file.WriteWithTab("	record_data.set_%s(static_cast<unsigned short>(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"%s\")));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeInt:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUnsignedInt:
			{
				file.WriteWithTab("	record_data.set_%s(static_cast<unsigned int>(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"%s\")));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeInt: 64:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetLongLong(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeFloat:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetFloat(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeString:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetString(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeBlob:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetString(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeUuid:
			{
				file.WriteWithTab("	record_data.set_%s(xenon::util_component::CSqlResultHelper::GetUUID(sql_result, \"%s\"));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		case dios::kDatabaseColTypeChar:
			{
				file.WriteWithTab("	record_data.set_%s(static_cast<char>(xenon::util_component::CSqlResultHelper::GetInt(sql_result, \"%s\")));\n", table_col_info.name().c_str(), table_col_info.name().c_str());
			}
			break;
		}
	}
	file.WriteWithTab("}\n");
}