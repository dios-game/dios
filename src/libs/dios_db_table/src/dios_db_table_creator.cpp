#include "precompiled.h"
#include "dios_db_table_creator.h"

#include <assert.h>
#include <list>

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = 0; } }

NS_DS_BEGIN

// 字段类型信息体;
struct RecordColTypeInfo {

	DatabaseColType record_col_type;
	std::string data_type_name;
	ds_uint32 data_num_lenth;
	ds_uint32 data_char_lenth;
	ds_boolean unsigned_flag;
};

// 字段类型信息声明;
static RecordColTypeInfo database_col_info[kDatabaseColTypeMax] = {

	{ kDatabaseColTypeNil, "null", 0, 0, false },
	{ kDatabaseColTypeSmallInt, "smallint", 6, 0, false },
	{ kDatabaseColTypeUnsignedSmallInt, "smallint", 5, 0, true },
	{ kDatabaseColTypeInt, "int", 11, 0, false },
	{ kDatabaseColTypeUnsignedSmallInt, "int", 10, 0, true },
	{ kDatabaseColTypeInt64, "bigint", 19, 0, false },
	{ kDatabaseColTypeFloat, "float", 12, 0, false },
	{ kDatabaseColTypeString, "varchar", 0, 0, false },
	{ kDatabaseColTypeBlob, "blob", 0, 0, false },
	{ kDatabaseColTypeUuid, "varchar", 0, 36, false },
	{ kDatabaseColTypeChar, "char", 1, 0, false },
};

ds_boolean CDatabaseTableCreator::CreateTable( com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info ) 
{
	// 判断是否存在字段;
	if(table_info.col_info_vector().size() == 0) {
		return false;
	}

	// 创建表单;
	char sql[1024];
	com::SqlQueryError sql_query_error = com::SQL_QUERY_ERROR_OK;
	sprintf(sql, "create table if not exists %s (id int(10) unsigned primary key auto_increment)", table_info.name().c_str());
	sql_connector->ExecuteSql(sql, sql_query_error);

	// 创建字段，索引与外键;
	if(!_CreateCol(sql_connector, table_info) || 
		!_CreateIndex(sql_connector, table_info) || 
		!_CreateForeignKey(sql_connector, table_info))
	{
		return false;
	}
	return true;
}

ds_boolean CDatabaseTableCreator::_CreateCol( com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info )
{
	char sql[4096];
	com::SqlQueryError sql_query_error = com::SQL_QUERY_ERROR_OK;
	ds_uint32 size = 0;
	char col_type_string[64];

	// 确认表信息中的字段个数是否有效;
	auto col_info_count = table_info.col_info_vector().size();
	if(col_info_count == 0) {
		return false;
	}

	// 查询当前表是否拥有指定字段;
	sprintf(sql, "show columns from %s", table_info.name().c_str());
	auto sql_result = sql_connector->ExecuteSql(sql, sql_query_error);
	if(!sql_result) {
		return false;
	}

	// 保存一张现有字段表单;
	std::map<std::string, std::string> exists_col_type_map;
	while(sql_result->FetchRow()) {

		std::string field_name = sql_result->GetFieldValueByName("Field", size);
		std::string type_name = sql_result->GetFieldValueByName("Type", size);
		exists_col_type_map[field_name] = type_name;
	}

	// 创建与调整表单;
	for(ds_int32 i=0; i<col_info_count; ++i)
	{
		auto &col = table_info.col_info_vector()[i];
		auto col_type = col.type();

		// 组织类型字符串;
		ds_uint32 col_size = 0;
		if(database_col_info[col_type].data_num_lenth) {
			col_size = database_col_info[col_type].data_num_lenth;
		}
		else if(database_col_info[col_type].data_char_lenth) {
			col_size = database_col_info[col_type].data_char_lenth;
		}
		else {
			col_size = col.char_size();
		}

		if(col_type == kDatabaseColTypeBlob || col_type == kDatabaseColTypeFloat) {
			sprintf(col_type_string, "%s", database_col_info[col_type].data_type_name);
		}
		else {
			sprintf(col_type_string, "%s(%u)%s", 
				database_col_info[col_type].data_type_name, 
				col_size, 
				database_col_info[col_type].unsigned_flag ? " unsigned" : "");
		}

		// 检测字段有效性;
		ds_boolean sql_error = false;

		// 如果字段不存在，则创建该字段;
		auto iter_exists_col_type = exists_col_type_map.find(col.name());
		if(iter_exists_col_type == exists_col_type_map.end()) {

			sprintf(sql, "alter table %s add %s %s", 
				table_info.name().c_str(), 
				col.name().c_str(), 
				col_type_string);

			sql_connector->ExecuteSql(sql, sql_query_error);
			if(sql_query_error != com::SQL_QUERY_ERROR_OK) {
				sql_error = true;
			}
		}
		// 如果字段存在，则验证该字段;
		else {

			if(iter_exists_col_type->second != col_type_string) {
				sql_error = true;
			}
		}
		if(sql_error) {
			return false;
		}
	}
	return true;
}

ds_boolean CDatabaseTableCreator::_CreateIndex( com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info )
{
	char sql[4096];
	ds_uint32 size = 0;
	com::SqlQueryError sql_query_error = com::SQL_QUERY_ERROR_OK;

	// 判断索引数量是否合法;
	auto index_count = table_info.index_info_vector().size();
	if(index_count == 0) {
		return true;
	}

	// 获取当前表单下的索引;
	sprintf(sql, "show index from %s", table_info.name().c_str());
	auto sql_result = sql_connector->ExecuteSql(sql, sql_query_error);
	if(!sql_result) {
		return false;
	}

	// 保存一张临时索引表;
	std::map<std::string, std::list<std::string> > exists_index_col_list_map;
	while(sql_result->FetchRow()) {

		std::string key_name = sql_result->GetFieldValueByName("Key_name", size);
		std::string col_name = sql_result->GetFieldValueByName("Column_name", size);
		exists_index_col_list_map[key_name].push_back(col_name);
	}

	// 创建与调整表单索引;
	for(ds_int32 i=0; i<index_count; i++)
	{
		auto &index_info = table_info.index_info_vector()[i];
		auto &exists_col_info_list = exists_index_col_list_map[index_info.name()];

		// 索引不存在，则创建新索引;
		if(exists_col_info_list.size() == 0) {

			// 组织索引创建语句;
			sprintf(sql, "create index %s on %s (", 
				index_info.name().c_str(),
				table_info.name().c_str());
			for(int j=0; j<index_info.col_name_array().size(); j++) {
				sprintf(sql+strlen(sql), "%s,", index_info.col_name_array()[j].c_str());
			}
			sprintf(sql+strlen(sql)-1, ")");

			// 执行创建语句;
			sql_connector->ExecuteSql(sql, sql_query_error);
			if(sql_query_error != com::SQL_QUERY_ERROR_OK) {
				return false;
			}
		}
		// 已存在索引，需要验证一下是否匹配;
		else {

			// 判断数量是否统一;
			if(exists_col_info_list.size() != index_info.col_name_array().size()) {
				return false;
			}

			// 判断字段名称是否统一;
			auto iter_exists_col_info = exists_col_info_list.begin();
			while(iter_exists_col_info != exists_col_info_list.end()) {

				ds_int32 j = 0;
				for(j=0; j<index_info.col_name_array().size(); j++) {

					if(index_info.col_name_array()[j] == (*iter_exists_col_info)) {
						break;
					}
				}
				if(j == index_info.col_name_array().size()) {
					return false;
				}
				++iter_exists_col_info;
			}
		}
	}
	return true;
}

ds_boolean CDatabaseTableCreator::_CreateForeignKey( com::ISqlConnector::Ptr sql_connector, const CDatabaseTableInfo& table_info )
{
	char sql[4096];
	com::SqlQueryError sql_query_error = com::SQL_QUERY_ERROR_OK;

	// 判断是否存在外键;
	ds_uint32 foreign_key_info_count = table_info.foreign_key_info_vector().size();
	if(foreign_key_info_count == 0) {
		return true;
	}

	// 获取当前已存在的外键信息;
	sprintf(sql, "select * from information_schema.KEY_COLUMN_USAGE where table_name='%s' and REFERENCED_COLUMN_NAME > ''",
		table_info.name().c_str());
	auto sql_result = sql_connector->ExecuteSql(sql, sql_query_error);
	if(!sql_result) {
		return false;
	}

	// 创建临时外键信息表单;
	std::vector<CDatabaseForeignKeyInfo> exists_foreign_key_info_array;
	auto exists_foreign_key_count = sql_result->GetRowCount();
	if(exists_foreign_key_count > 0) {
		exists_foreign_key_info_array.resize(exists_foreign_key_count);

		ds_int32 extend_key_index = 0;
		while(sql_result->FetchRow()) {

			ds_uint32 size = 0;
			exists_foreign_key_info_array[extend_key_index].set_name(sql_result->GetFieldValueByName("constraint_name", size));
			exists_foreign_key_info_array[extend_key_index].set_col_name(sql_result->GetFieldValueByName("column_name", size));
			exists_foreign_key_info_array[extend_key_index].set_foreign_table_name(sql_result->GetFieldValueByName("referenced_table_name", size));
			exists_foreign_key_info_array[extend_key_index].set_foreign_col_name(sql_result->GetFieldValueByName("referenced_column_name", size));

			++extend_key_index;
		}
	}

	// 判断外键是否匹配;
	ds_boolean have_error = false;
	for(ds_int32 i=0; i<foreign_key_info_count; i++) {
		ds_int32 j = 0;
		for(j=0; j<exists_foreign_key_count; j++) {
			if(exists_foreign_key_info_array[j].name() == table_info.foreign_key_info_vector()[i].name()) {
				if(exists_foreign_key_info_array[j] != table_info.foreign_key_info_vector()[i]) {
					have_error = true;
				}
				break;
			}
		}

		// 创建新的外键;
		if(j == exists_foreign_key_count) {

			auto &extend_key = table_info.foreign_key_info_vector()[j];
			sprintf(sql, "alter table %s add constraint %s foreign key (%s) references %s (%s) on delete no action on update cascade", 
				table_info.name().c_str(), 
				extend_key.name().c_str(),
				extend_key.col_name().c_str(), 
				extend_key.foreign_table_name().c_str(),
				extend_key.foreign_col_name().c_str());

			sql_connector->ExecuteSql(sql, sql_query_error);
			if(sql_query_error != com::SQL_QUERY_ERROR_OK) {
				have_error = true;
			}
		}
		if(have_error) {
			break;
		}
	}
	return !have_error;
}

NS_DS_END
