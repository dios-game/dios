#ifndef DIOS_DB_MULTI_RECORDSET_H
#define DIOS_DB_MULTI_RECORDSET_H

#include "dios_db_custom_lib.h"

#include <list>
#include <map>
#include <mutex>
#include "dios_util/util_memory.hpp"

NS_DS_BEGIN

class CDatabaseCustomRecord;

/*
 *	����¼����;
 */
class DIOS_DB_CUSTOM_DECL CDBMultiRecordSet
{
public:
	typedef std::list<std::shared_ptr<CDatabaseCustomRecord> > RecordLiteList;

	CDBMultiRecordSet(void);
	~CDBMultiRecordSet(void);

	// ���ü�¼;
	template<class Record>
	void SetRecord(std::shared_ptr<Record> record) {

		// ת����¼����;
		RecordLiteList record_lite_list;
		record_lite_list.push_back(record);

		// ��Ӽ�¼������;
		mutex_.lock();
		record_lite_list_map_[typeid(Record).name()] = record_lite_list;
		mutex_.unlock();
	}

	// ��ȡ��¼;
	template<class Record>
	std::shared_ptr<Record> GetRecord(void) {

		ds_boolean is_successful = false;

		// �ӱ��г�ȡ;
		std::shared_ptr<Record> record;

		mutex_.lock();
		auto iter_record_list = record_lite_list_map_.find(typeid(Record).name());
		if(iter_record_list != record_lite_list_map_.end()) {

			auto iter_record = iter_record_list->second.begin();
			while(iter_record != iter_record_list->second.end()) {

				record = util::CMemory::DynamicCast<Record>(*iter_record);
				if(record) {
					break;
				}
				++iter_record;
			}
		}
		mutex_.unlock();

		return record;
	}

	// ���ü�¼����;
	template<class Record>
	void SetRecordList(const std::list<std::shared_ptr<Record> >& record_list) {

		// ת����¼����;
		RecordLiteList record_lite_list;
		auto iter_record = record_list.begin();
		while(iter_record != record_list.end()) {

			record_lite_list.push_back(*iter_record);
			++iter_record;
		}

		// ��Ӽ�¼������;
		mutex_.lock();
		record_lite_list_map_[typeid(Record).name()] = record_lite_list;
		mutex_.unlock();
	}

	// ��ȡ��¼����;
	template<class Record>
	std::list<std::shared_ptr<Record> > GetRecordList(void) {
		
		ds_boolean is_successful = false;

		// �ӱ��г�ȡ;
		std::list<std::shared_ptr<Record> > record_list;

		mutex_.lock();
		auto iter_record_list = record_lite_list_map_.find(typeid(Record).name());
		if(iter_record_list != record_lite_list_map_.end()) {

			auto iter_record = iter_record_list->second.begin();
			while(iter_record != iter_record_list->second.end()) {

				auto record = (*iter_record)->QueryInterface<Record>();
				if(record) {
					record_list.push_back(record);
				}
				++iter_record;
			}
		}
		mutex_.unlock();

		return record_list;
	}

private:
	std::map<std::string, RecordLiteList> record_lite_list_map_; // ��;
	std::mutex mutex_; // �ٽ���;
};

NS_DS_END

#endif