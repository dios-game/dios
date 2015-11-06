#include "precompiled.h"
#include "dios_db_sql_custom.h"

#include "dios_db_table/dios_db_table_creator.h"

#include "dios_db_custom.h"

NS_DS_BEGIN

void BaseDatabaseSqlCommitInsert( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	auto sql_connector = sDatabaseCustomEnv->GetSqlConnector();
	ds_boolean successful = true;
	if(sql_connector) {
		successful = record->CommitInsert(sql_connector);
	}
	if(func) {
		func(successful);
	}
}

void BaseDatabaseSqlCommitUpdate( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	auto sql_connector = sDatabaseCustomEnv->GetSqlConnector();
	ds_boolean successful = true;
	if(sql_connector && record->IsDirty()) {
		successful = record->CommitUpdate(sql_connector);
	}
	if(func) {
		func(successful);
	}
}

void BaseDatabaseSqlCommitDelete( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	auto sql_connector = sDatabaseCustomEnv->GetSqlConnector();
	ds_boolean successful = true;
	if(sql_connector) {
		successful = record->CommitDelete(sql_connector);
	}
	if(func) {
		func(successful);
	}
}

CDatabaseSqlCommitTool::CDatabaseSqlCommitTool( void )
{
	auto task_service = sDatabaseCustomEnv->task_service();
	if(task_service) {
		strand_task_ = task_service->CreateStrandTask();
	}
}

CDatabaseSqlCommitTool::~CDatabaseSqlCommitTool( void )
{

}

void CDatabaseSqlCommitTool::CommitInsert( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	if(strand_task_) {
		strand_task_->Post([=](){ BaseDatabaseSqlCommitInsert(record, func); });
	}
}

void CDatabaseSqlCommitTool::CommitUpdate( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	if(!record->IsDirty()) {
		if(func) {
			func(true);
		}
		return;
	}

	if(strand_task_) {
		strand_task_->Post([=](){ BaseDatabaseSqlCommitUpdate(record, func); });
	}
}

void CDatabaseSqlCommitTool::CommitDelete( IDatabaseSqlCommitRecord::Ptr record, std::function<void(ds_boolean)> func )
{
	if(strand_task_) {
		strand_task_->Post([=](){ BaseDatabaseSqlCommitDelete(record, func); });
	}
}

void BaseDatabaseSqlCommitCreateTable( const CDatabaseTableInfo& database_table, std::function<void(ds_boolean)> func )
{
	auto sql_connector = sDatabaseCustomEnv->GetSqlConnector();
	ds_boolean successful = false;
	if(sql_connector) {
		successful = sDatabaseTableCreator->CreateTable(sql_connector, database_table);
	}
	if(func) {
		func(successful);
	}
}

void BaseDatabaseSqlCreateTable( CDatabaseCustomTable* database_custom_table, std::function<void(ds_boolean)> func )
{
	auto task_service = sDatabaseCustomEnv->task_service();
	if(task_service) {
		task_service->Post([=](){ BaseDatabaseSqlCommitCreateTable(database_custom_table->table(), func); });
	}
}

void BaseDatabaseSqlCommitSelectRecordSet( std::function<void(com::ISqlConnector::Ptr)> func )
{
	auto sql_connector = sDatabaseCustomEnv->GetSqlConnector();
	if(func) {
		func(sql_connector);
	}
}

void BaseDatabaseSqlSelectRecordSet( std::function<void(com::ISqlConnector::Ptr)> func )
{
	auto task_service = sDatabaseCustomEnv->task_service();
	if(task_service) {
		task_service->Post([=](){ BaseDatabaseSqlCommitSelectRecordSet(func); });
	}
}

NS_DS_END
