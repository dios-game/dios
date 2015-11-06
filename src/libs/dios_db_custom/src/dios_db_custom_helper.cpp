#include "precompiled.h"
#include "dios_db_custom_helper.h"

NS_DS_BEGIN

CBatchCreateTableData::~CBatchCreateTableData( void )
{

}

CBatchCreateTableData::CBatchCreateTableData( void ) : todo_list_(new util::CBatchTaskList)
{
	is_successful_ = true;
}


CBatchSelectRecordSetData::~CBatchSelectRecordSetData( void )
{

}

CBatchSelectRecordSetData::CBatchSelectRecordSetData( void ) : todo_list_(new util::CBatchTaskList),
	multi_recordset_(new CDBMultiRecordSet)
{

}

void CDatabaseCustomHelper::_ReleaseCurrentBatchSelectRecordSetData( void )
{
	tls_batch_select_recordset_data_.release();
}

std::shared_ptr<CBatchSelectRecordSetData> CDatabaseCustomHelper::_GetCurrentBatchSelectRecordSetData( void )
{
	auto batch_select_recordset_data = tls_batch_select_recordset_data_.get();
	if(!batch_select_recordset_data) {
		batch_select_recordset_data = new std::shared_ptr<CBatchSelectRecordSetData>(new CBatchSelectRecordSetData);
		tls_batch_select_recordset_data_.reset(batch_select_recordset_data);
	}
	return *batch_select_recordset_data;
}

void CDatabaseCustomHelper::_ReleaseCurrentBatchCreateTableData( void )
{
	tls_batch_create_table_data_.release();
}

std::shared_ptr<CBatchCreateTableData> CDatabaseCustomHelper::_GetCurrentBatchCreateTableData( void )
{
	auto batch_create_table_data = tls_batch_create_table_data_.get();
	if(!batch_create_table_data) {
		batch_create_table_data = new std::shared_ptr<CBatchCreateTableData>(new CBatchCreateTableData);
		tls_batch_create_table_data_.reset(batch_create_table_data);
	}
	return *batch_create_table_data;
}

std::shared_ptr<CDBMultiRecordSet> CDatabaseCustomHelper::StartBatchSelectRecordSetSync( void )
{
	std::shared_ptr<CDBMultiRecordSet> result;

	std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
	StartBatchSelectRecordSet([&result, barrier](std::shared_ptr<CDBMultiRecordSet> multi_record){
		result = multi_record;
		barrier->wait();
	});
	barrier->wait();

	return result;
}

void CDatabaseCustomHelper::StartBatchSelectRecordSet( std::function<void(std::shared_ptr<CDBMultiRecordSet>)> callback )
{
	auto data = _GetCurrentBatchSelectRecordSetData();
	if(data && data->todo_list()) {
		data->todo_list()->DoAllTask([this, data, callback](){ if(callback) { callback(data->multi_recordset()); } });
	}
	_ReleaseCurrentBatchSelectRecordSetData();
}

ds_boolean CDatabaseCustomHelper::StartBatchCreateTableSync( void )
{
	ds_boolean result = false;

	std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
	StartBatchCreateTable([&result, barrier](ds_boolean is_successful){ 
		result = is_successful;
		barrier->wait();
	});
	barrier->wait();

	return result;
}

void CDatabaseCustomHelper::StartBatchCreateTable( std::function<void(ds_boolean)> callback )
{
	auto data = _GetCurrentBatchCreateTableData();
	if(data && data->todo_list()) {
		data->todo_list()->DoAllTask([this, callback, data](){ 
			if(callback) { 
				callback(data->is_successful()); 
			}
		});
	}
}

CDatabaseCustomHelper::~CDatabaseCustomHelper( void )
{

}

CDatabaseCustomHelper::CDatabaseCustomHelper( void )
{

}

NS_DS_END
