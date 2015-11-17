#include "precompiled.h"
#include "database_define_custom_cache_class.h"


void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassBegin( CCodeFile& file, const std::string& decl_name )
{
	file->WriteWithTab("/* \n");
	file->WriteWithTab(" *	Cache操作类\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("class %s Cache\n", decl_name.c_str());
	file->WriteWithTab("{\n");
}

/*
 *	Cache操作类结尾
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassEnd( CCodeFile& file )
{
	file->WriteWithTab("};\n");
}

/*
 *	建表函数
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassCreateTable( CCodeFile& file )
{
	file->WriteWithTab("static void CreateTable(const std::string& dest_id, boost::function<void(bool)> func);\n");
}

/*
 *	结果转为记录
 */
void DatabaseDefineCustomCacheClass::WriteHeaderResult2Record( CCodeFile& file )
{
	file->WriteWithTab("static void SelectResult2Record(TableRecordSetBuffer* table_recordset_buffer, \n");
	file->WriteWithTab("								bool is_end, \n");
	file->WriteWithTab("								std::string dest_id, \n");
	file->WriteWithTab("								boost::function<void(const std::list<Record::Ptr>&)> func, \n");
	file->WriteWithTab("								boost::shared_ptr<std::list<Record::Ptr> > record_list);\n");
}

/*
 *	缓存函数
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassCacheRecordSet( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file->WriteWithTab("static void CacheRecordSet(const std::string& dest_id, boost::function<void(bool)> func);\n");
	int table_key_count = table_info.GetTableKeyDescCount();
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);
		file->WriteWithTab("static void CacheRecordSet(const std::string& dest_id, const KEY_%s& key, boost::function<void(bool)> func);\n", upper_table_key_name.c_str());
	}
}

/*
 *	查询函数
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassSelectRecordSet( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file->WriteWithTab("static void SelectRecordSet(const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func);\n");
	int table_key_count = table_info.GetTableKeyDescCount();
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);
		file->WriteWithTab("static void SelectRecordSet(const std::string& dest_id, const KEY_%s& key, boost::function<void(const std::list<Record::Ptr>&)> func);\n", upper_table_key_name.c_str());
	}
}

/*
 *	关闭缓存函数
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClassReleaseRecordSet( CCodeFile& file, dios::CDatabaseTableInfo& table_info )
{
	int table_key_count = table_info.GetTableKeyDescCount();
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);
		file->WriteWithTab("static void ReleaseRecordSet(const std::string& dest_id, const KEY_%s& key);\n", upper_table_key_name.c_str());
	}
}

/*
 *	Cache操作类组合
 */
void DatabaseDefineCustomCacheClass::WriteHeaderDatabaseCacheClass( CCodeFile& file, dios::CDatabaseTableInfo& table_info, const std::string& decl_name )
{
	WriteHeaderDatabaseCacheClassBegin(file, decl_name);
	file->WriteWithTab("public:\n");
	file->IncreaseTab();
	WriteHeaderDatabaseCacheClassCreateTable(file);
	WriteHeaderDatabaseCacheClassSelectRecordSet(file, table_info);
	WriteHeaderDatabaseCacheClassCacheRecordSet(file, table_info);
	WriteHeaderDatabaseCacheClassReleaseRecordSet(file, table_info);
	file->DecreaseTab();
	WriteHeaderDatabaseCacheClassEnd(file);
}

void DatabaseDefineCustomCacheClass::WriteSourceDatabaseCacheClass( CCodeFile& file, dios::CDatabaseTableInfo& table_info )
{
	WriteSourceCreateTable(file);
	file->WriteWithTab("\n");
	WriteSourceResult2Record(file);
	file->WriteWithTab("\n");
	WriteSourceCacheRecordSet(file, table_info);
	file->WriteWithTab("\n");
	WriteSourceSelectRecordSet(file, table_info);
	file->WriteWithTab("\n");
	WriteSourceReleaseRecordSet(file, table_info);
}

/*
 *	建表函数
 */
void DatabaseDefineCustomCacheClass::WriteSourceCreateTable( CCodeFile& file )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	建表操作\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("void Cache::CreateTable( const std::string& dest_id, boost::function<void(bool)> func ) {\n");
	file->WriteWithTab("	BaseDatabaseCacheCreateTable(dest_id, Info::GetInstancePtr(), func);\n");
	file->WriteWithTab("}\n");
}

/*
 *	记录集转换为记录
 */
void DatabaseDefineCustomCacheClass::WriteSourceResult2Record( CCodeFile& file )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	TableRecordSetBuffer转换为Record::Ptr\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("static void SelectResult2Record( TableRecordSetBuffer* table_recordset_buffer, \n");
	file->WriteWithTab("								bool is_end, \n");
	file->WriteWithTab("								std::string dest_id, \n");
	file->WriteWithTab("								boost::function<void(const std::list<Record::Ptr>&)> func, \n");
	file->WriteWithTab("								boost::shared_ptr<std::list<Record::Ptr> > record_list )\n");
	file->WriteWithTab("{\n");
	file->WriteWithTab("	if(!func) {\n");
	file->WriteWithTab("		return;\n");
	file->WriteWithTab("	}\n");
	file->WriteWithTab("	\n");
	file->WriteWithTab("	int pos = 0;\n");
	file->WriteWithTab("	for(int i=0; i<table_recordset_buffer->record_count; ++i)\n");
	file->WriteWithTab("	{\n");
	file->WriteWithTab("		RecordImpl::Ptr record(new RecordImpl);\n");
	file->WriteWithTab("		record->InitCommitObject(kDatabaseCacheCustom, dest_id.c_str(), kCommitStatusUpdate);\n");
	file->WriteWithTab("		record->record_data().ParseFromArray(table_recordset_buffer->record_set_mem+pos, table_recordset_buffer->buffer_size-pos);\n");
	file->WriteWithTab("		record->record_data().clear_record_dirty();\n");
	file->WriteWithTab("		pos += record->record_data().ByteSize();\n");
	file->WriteWithTab("		record_list->push_back(record);\n");
	file->WriteWithTab("	}\n");
	file->WriteWithTab("	if(is_end) {\n");
	file->WriteWithTab("		func(*record_list);\n");
	file->WriteWithTab("	}\n");
	file->WriteWithTab("}\n");
}

/*
 *	缓存函数
 */
void DatabaseDefineCustomCacheClass::WriteSourceCacheRecordSet( CCodeFile& file, const dios::CDatabaseTableInfo& table_info )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	缓存整表操作\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("void Cache::CacheRecordSet( const std::string& dest_id, boost::function<void(bool)> func ) {\n");
	file->WriteWithTab("	BaseDatabaseCacheCacheRecordSet(dest_id, Info::GetInstancePtr(), func);\n");
	file->WriteWithTab("}\n");
	file->WriteWithTab("\n");

	int table_key_count = table_info.GetTableKeyDescCount();
	if(table_key_count > 0) {
		file->WriteWithTab("/*\n");
		file->WriteWithTab(" *	根据索引缓存操作\n");
		file->WriteWithTab(" */\n");
	}
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);

		file->WriteWithTab("void Cache::CacheRecordSet( const std::string& dest_id, const KEY_%s& key, boost::function<void(bool)> func ) {\n", upper_table_key_name.c_str());
		file->WriteWithTab("	DBC_KEY_%s dbc_key(key);\n", upper_table_key_name.c_str());
		file->WriteWithTab("	BaseDatabaseCacheCacheRecordSet(dest_id, Info::GetInstancePtr(), &dbc_key, func);\n");
		file->WriteWithTab("}\n");

		if(i != table_key_count-1) {
			file->WriteWithTab("\n");
		}
	}
}

/*
 *	查询函数
 */
void DatabaseDefineCustomCacheClass::WriteSourceSelectRecordSet( CCodeFile& file, dios::CDatabaseTableInfo& table_info )
{
	file->WriteWithTab("/*\n");
	file->WriteWithTab(" *	查询整表操作\n");
	file->WriteWithTab(" */\n");
	file->WriteWithTab("void Cache::SelectRecordSet( const std::string& dest_id, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n");
	file->WriteWithTab("	std::string temp_dest_id(dest_id);\n");
	file->WriteWithTab("	boost::shared_ptr<std::list<Record::Ptr> > record_list(new std::list<Record::Ptr>);\n");
	file->WriteWithTab("	BaseDatabaseCacheSelectRecordSet(dest_id, Info::GetInstancePtr(), boost::bind(SelectResult2Record, _1, _2, temp_dest_id, func, record_list));\n");
	file->WriteWithTab("}\n");
	file->WriteWithTab("\n");

	int table_key_count = table_info.GetTableKeyDescCount();
	if(table_key_count > 0) {
		file->WriteWithTab("/*\n");
		file->WriteWithTab(" *	根据索引查询操作\n");
		file->WriteWithTab(" */\n");
	}
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);

		file->WriteWithTab("void Cache::SelectRecordSet( const std::string& dest_id, const KEY_%s& key, boost::function<void(const std::list<Record::Ptr>&)> func ) {\n", upper_table_key_name.c_str());
		file->WriteWithTab("	std::string temp_dest_id(dest_id);\n");
		file->WriteWithTab("	DBC_KEY_%s dbc_key(key);\n", upper_table_key_name.c_str());
		file->WriteWithTab("	boost::shared_ptr<std::list<Record::Ptr> > record_list(new std::list<Record::Ptr>);\n");
		file->WriteWithTab("	BaseDatabaseCacheSelectRecordSet(dest_id, Info::GetInstancePtr(), &dbc_key, boost::bind(SelectResult2Record, _1, _2, temp_dest_id, func, record_list));\n");
		file->WriteWithTab("}\n");

		if(i != table_key_count-1) {
			file->WriteWithTab("\n");
		}
	}
}

/*
 *	关闭缓存函数
 */
void DatabaseDefineCustomCacheClass::WriteSourceReleaseRecordSet( CCodeFile& file, dios::CDatabaseTableInfo& table_info )
{
	int table_key_count = table_info.GetTableKeyDescCount();
	if(table_key_count > 0) {
		file->WriteWithTab("/*\n");
		file->WriteWithTab(" *	根据索引关闭缓存操作\n");
		file->WriteWithTab(" */\n");
	}
	for(int i=0; i<table_key_count; ++i)
	{
		tableinfo_project::TableKeyDesc * table_index_info = table_info.GetTableKeyDesc(i);
		std::string upper_table_key_name = table_index_info->index_name;
		boost::algorithm::to_upper(upper_table_key_name);

		file->WriteWithTab("void Cache::ReleaseRecordSet( const std::string& dest_id, const KEY_%s& key ) {\n", upper_table_key_name.c_str());
		file->WriteWithTab("	DBC_KEY_%s dbc_key(key);\n", upper_table_key_name.c_str());
		file->WriteWithTab("	BaseDatabaseCacheReleaseRecordSet(dest_id, Info::GetInstancePtr(), &dbc_key);\n");
		file->WriteWithTab("}\n");

		if(i != table_key_count-1) {
			file->WriteWithTab("\n");
		}
	}
}
