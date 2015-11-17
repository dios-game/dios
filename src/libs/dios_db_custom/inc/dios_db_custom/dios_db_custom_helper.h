#ifndef DATABASE_CUSTOM_HELPER_H
#define DATABASE_CUSTOM_HELPER_H

#include "dios_db_custom_lib.h"

#include <list>
#include "boost/thread.hpp"

#include "dios/platform.h"
#include "dios_util/util_batch_task_list.h"

#include "dios_db_multi_recordset.h"

NS_DS_BEGIN

/*
 *	批量表单创建数据;
 */
class DIOS_DB_CUSTOM_DECL CBatchCreateTableData
{
public:
	CBatchCreateTableData(void);
	~CBatchCreateTableData(void);

	DS_PROPERTY(std::shared_ptr<util::CBatchTaskList>, todo_list); // 待办列表;
	DS_PROPERTY(ds_boolean, is_successful); // 执行结果;
};

/*
 *	批量表单读取数据;
 */
class DIOS_DB_CUSTOM_DECL CBatchSelectRecordSetData
{
public:
	CBatchSelectRecordSetData(void);
	~CBatchSelectRecordSetData(void);

	DS_PROPERTY(std::shared_ptr<util::CBatchTaskList>, todo_list); // 待办列表;
	DS_PROPERTY(std::shared_ptr<CDBMultiRecordSet>, multi_recordset); // 多表记录集合;
};

/*
 *	自定义数据库助手;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomHelper
{
public:
	CDatabaseCustomHelper(void);
	~CDatabaseCustomHelper(void);

	// 异步创建表单;
	template<class Table>
	void CreateTable(const std::string& dest_id, std::function<void(ds_boolean)> callback) {

		Table::CreateTable(dest_id, [callback](ds_boolean is_successful){ 
			if(callback) {
				callback(is_successful);
			}
		});
	}

	// 同步创建表单;
	template<class Table>
	ds_boolean CreateTableSync(const std::string& dest_id) {

		ds_boolean result = false;

		std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
		CreateTable<Table>(dest_id, [&result, barrier](ds_boolean is_successful){
			result = is_successful;
			barrier->wait();
		});
		barrier->wait();

		return result;
	}

	// 推入创建表单批量任务;
	template<class Table>
	void BatchCreateTable(const std::string& dest_id) {

		auto data = _GetCurrentBatchCreateTableData();
		if(data && data->todo_list()) {
			data->todo_list()->AddUncompletedTaskRef();
			data->todo_list()->PushTask([this, data, dest_id](){ _DoCreateTableTask<Table>(data, dest_id); });
		}
	}

	// 异步执行创建表单批量任务;
	void StartBatchCreateTable(std::function<void(ds_boolean)> callback);

	// 阻塞执行创建表单批量任务;
	ds_boolean StartBatchCreateTableSync(void);

	// 异步读取全表记录;
	template<class Table, class Record>
	void SelectRecordSet(const std::string& dest_id, boost::function<void(const std::list<std::shared_ptr<Record> >&)> callback) {

		Table::SelectRecordSet(dest_id, [callback](const std::list<Record::Ptr>& record_list){ 
			if(callback) {
				callback(record_list);
			}
		});
	}

	// 同步读取单条记录;
	template<class Table, class Record>
	std::shared_ptr<Record> SelectRecordSetSync(const std::string& dest_id) {

		std::shared_ptr<Record> result;

		std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
		SelectRecordSet<Table, Record>(dest_id, [&result, barrier](const std::list<std::shared_ptr<Record> >& record_list){

			if(record_list.size() > 0) {
				result = *record_list.begin();
			}
			barrier->wait();
		});
		barrier->wait();

		return result;
	}

	// 同步读取全表记录;
	template<class Table, class Record>
	std::list<std::shared_ptr<Record> > SelectRecordSetSync(const std::string& dest_id) {

		std::list<std::shared_ptr<Record> > result;

		std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
		SelectRecordSet<Table, Record>(dest_id, [&result, barrier](const std::list<std::shared_ptr<Record> >& record_list){
			result = record_list;
			barrier->wait();
		});
		barrier->wait();

		return result;
	}

	// 异步读取搜索记录;
	template<class Table, class Index, class Record>
	void SelectRecordSet(const std::string& dest_id, const Index& index, std::function<void(const std::list<std::shared_ptr<Record> >&)> callback) {

		Table::SelectRecordSet(dest_id, index, [callback](const std::list<Record::Ptr>& record_list){ 
			if(callback) {
				callback(record_list);
			}
		});
	}

	// 同步读取搜索记录;
	template<class Table, class Index, class Record>
	std::list<std::shared_ptr<Record> > SelectRecordSetSync(const std::string& dest_id, const Index& index) {

		std::list<std::shared_ptr<Record> > result;

		std::shared_ptr<boost::barrier> barrier(new boost::barrier(2));
		SelectRecordSet<Table, Index, Record>(dest_id, index, [&result, barrier](const std::list<Record::Ptr>& record_list){ 
			result = record_list;
			barrier->wait();
		});
		barrier->wait();
		return result;
	}

	// 推入读取任务;
	template<class Table, class Record>
	void BatchSelectRecordSet(const std::string& dest_id) {

		auto data = _GetCurrentBatchSelectRecordSetData();
		if(data && data->todo_list()) {
			data->todo_list()->AddUncompletedTaskRef();
			data->todo_list()->PushTask([this, data, dest_id](){ _DoSelectRecordSetTask<Table, Record>(data, dest_id); });
		}
		_ReleaseCurrentBatchCreateTableData();
	}

	template<class Table, class Index, class Record>
	void BatchSelectRecordSet(const std::string& dest_id, const Index& index) {

		auto data = _GetCurrentBatchSelectRecordSetData();
		if(data && data->todo_list()) {
			data->todo_list()->AddUncompletedTaskRef();
			data->todo_list()->PushTask([this, data, dest_id, index](){ _DoSelectRecordSetTask<Table, Index, Record>(data, dest_id, index); });
		}
	}

	// 异步执行读取批量任务;
	void StartBatchSelectRecordSet(std::function<void(std::shared_ptr<CDBMultiRecordSet>)> callback);

	// 同步执行读取批量任务;
	std::shared_ptr<CDBMultiRecordSet> StartBatchSelectRecordSetSync(void);

	DS_SINGLETON(CDatabaseCustomHelper);

private:

	// 创建任务回调;
	template<class Table>
	void _DoCreateTableTask(std::shared_ptr<CBatchCreateTableData> data, const std::string& dest_id) {
		Table::CreateTable(dest_id, [data](ds_boolean is_successful){ 
			if(!is_successful) { 
				data->set_is_successful(false); 
			} 
			data->todo_list()->ReleaseUncompletedTaskRef();
		});
	}

	// 读取任务回调;
	template<class Table, class Record>                                  
	void _DoSelectRecordSetTask(std::shared_ptr<CBatchSelectRecordSetData> data, const std::string& dest_id) {
		Table::SelectRecordSet(dest_id, [data](const std::list<Record::Ptr>& record_list){ 
			data->multi_recordset()->SetRecordList<Record>(record_list);
			data->todo_list()->ReleaseUncompletedTaskRef(); 
		});
	}

	template<class Table, class Index, class Record>
	void _DoSelectRecordSetTask(std::shared_ptr<CBatchSelectRecordSetData> data, const std::string& dest_id, const Index& index) {
		Table::SelectRecordSet(dest_id, index, [data](const std::list<Record::Ptr>& record_list){ 
			data->multi_recordset()->SetRecordList<Record>(record_list);
			data->todo_list()->ReleaseUncompletedTaskRef(); 
		});
	}

	// 获取当前任务列表;
	std::shared_ptr<CBatchCreateTableData> _GetCurrentBatchCreateTableData(void);

	// 释放当前任务列表;
	void _ReleaseCurrentBatchCreateTableData(void);

	// 获取当前任务列表;
	std::shared_ptr<CBatchSelectRecordSetData> _GetCurrentBatchSelectRecordSetData(void);

	// 释放当前任务列表;
	void _ReleaseCurrentBatchSelectRecordSetData(void);

	boost::thread_specific_ptr<std::shared_ptr<CBatchCreateTableData> > tls_batch_create_table_data_; // 建表数据TLS;
	boost::thread_specific_ptr<std::shared_ptr<CBatchSelectRecordSetData> > tls_batch_select_recordset_data_; // 读取数据TLS;
};

NS_DS_END

#define sDatabaseCustomHelper dios::CDatabaseCustomHelper::GetInstancePtr()

#endif