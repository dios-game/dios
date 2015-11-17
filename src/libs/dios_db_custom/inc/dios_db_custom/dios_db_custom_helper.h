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
 *	��������������;
 */
class DIOS_DB_CUSTOM_DECL CBatchCreateTableData
{
public:
	CBatchCreateTableData(void);
	~CBatchCreateTableData(void);

	DS_PROPERTY(std::shared_ptr<util::CBatchTaskList>, todo_list); // �����б�;
	DS_PROPERTY(ds_boolean, is_successful); // ִ�н��;
};

/*
 *	��������ȡ����;
 */
class DIOS_DB_CUSTOM_DECL CBatchSelectRecordSetData
{
public:
	CBatchSelectRecordSetData(void);
	~CBatchSelectRecordSetData(void);

	DS_PROPERTY(std::shared_ptr<util::CBatchTaskList>, todo_list); // �����б�;
	DS_PROPERTY(std::shared_ptr<CDBMultiRecordSet>, multi_recordset); // ����¼����;
};

/*
 *	�Զ������ݿ�����;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomHelper
{
public:
	CDatabaseCustomHelper(void);
	~CDatabaseCustomHelper(void);

	// �첽������;
	template<class Table>
	void CreateTable(const std::string& dest_id, std::function<void(ds_boolean)> callback) {

		Table::CreateTable(dest_id, [callback](ds_boolean is_successful){ 
			if(callback) {
				callback(is_successful);
			}
		});
	}

	// ͬ��������;
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

	// ���봴������������;
	template<class Table>
	void BatchCreateTable(const std::string& dest_id) {

		auto data = _GetCurrentBatchCreateTableData();
		if(data && data->todo_list()) {
			data->todo_list()->AddUncompletedTaskRef();
			data->todo_list()->PushTask([this, data, dest_id](){ _DoCreateTableTask<Table>(data, dest_id); });
		}
	}

	// �첽ִ�д�������������;
	void StartBatchCreateTable(std::function<void(ds_boolean)> callback);

	// ����ִ�д�������������;
	ds_boolean StartBatchCreateTableSync(void);

	// �첽��ȡȫ���¼;
	template<class Table, class Record>
	void SelectRecordSet(const std::string& dest_id, boost::function<void(const std::list<std::shared_ptr<Record> >&)> callback) {

		Table::SelectRecordSet(dest_id, [callback](const std::list<Record::Ptr>& record_list){ 
			if(callback) {
				callback(record_list);
			}
		});
	}

	// ͬ����ȡ������¼;
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

	// ͬ����ȡȫ���¼;
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

	// �첽��ȡ������¼;
	template<class Table, class Index, class Record>
	void SelectRecordSet(const std::string& dest_id, const Index& index, std::function<void(const std::list<std::shared_ptr<Record> >&)> callback) {

		Table::SelectRecordSet(dest_id, index, [callback](const std::list<Record::Ptr>& record_list){ 
			if(callback) {
				callback(record_list);
			}
		});
	}

	// ͬ����ȡ������¼;
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

	// �����ȡ����;
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

	// �첽ִ�ж�ȡ��������;
	void StartBatchSelectRecordSet(std::function<void(std::shared_ptr<CDBMultiRecordSet>)> callback);

	// ͬ��ִ�ж�ȡ��������;
	std::shared_ptr<CDBMultiRecordSet> StartBatchSelectRecordSetSync(void);

	DS_SINGLETON(CDatabaseCustomHelper);

private:

	// ��������ص�;
	template<class Table>
	void _DoCreateTableTask(std::shared_ptr<CBatchCreateTableData> data, const std::string& dest_id) {
		Table::CreateTable(dest_id, [data](ds_boolean is_successful){ 
			if(!is_successful) { 
				data->set_is_successful(false); 
			} 
			data->todo_list()->ReleaseUncompletedTaskRef();
		});
	}

	// ��ȡ����ص�;
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

	// ��ȡ��ǰ�����б�;
	std::shared_ptr<CBatchCreateTableData> _GetCurrentBatchCreateTableData(void);

	// �ͷŵ�ǰ�����б�;
	void _ReleaseCurrentBatchCreateTableData(void);

	// ��ȡ��ǰ�����б�;
	std::shared_ptr<CBatchSelectRecordSetData> _GetCurrentBatchSelectRecordSetData(void);

	// �ͷŵ�ǰ�����б�;
	void _ReleaseCurrentBatchSelectRecordSetData(void);

	boost::thread_specific_ptr<std::shared_ptr<CBatchCreateTableData> > tls_batch_create_table_data_; // ��������TLS;
	boost::thread_specific_ptr<std::shared_ptr<CBatchSelectRecordSetData> > tls_batch_select_recordset_data_; // ��ȡ����TLS;
};

NS_DS_END

#define sDatabaseCustomHelper dios::CDatabaseCustomHelper::GetInstancePtr()

#endif