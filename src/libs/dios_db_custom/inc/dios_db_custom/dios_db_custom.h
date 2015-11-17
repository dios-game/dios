#ifndef DIOS_DB_CUSTOM_H
#define DIOS_DB_CUSTOM_H

#include "dios_db_custom_lib.h"

#include <list>
#include "boost/thread/tss.hpp"

#include "component/com_task.h"
#include "component/com_sql.h"
#include "dios_db_table/dios_db_tableinfo.h"

#include "dios_db_commit_object.h"

NS_DS_BEGIN

// ��������;
enum DatabaseCustomType
{
	kDatabaseCustomTypeNil,	// δ����;
	kDatabaseCustomTypeSql,	// ���ݿ�ֱ�Ӳ�������;

	kDatabaseCustomTypeMax,
};

/*
 *	���Ƽ�¼����;
 */
class CDatabaseCustomRecord
{
public:
	virtual ~CDatabaseCustomRecord(void) {}
	
	// ������������;
	virtual void ParseFromArray(const void* buffer, ds_uint32 size) = 0;
	virtual void ParseFromString(const std::string& buffer) = 0;

	// ������������;
	virtual ds_boolean SerializeToArray(void* buffer, ds_uint32& size) = 0;
	virtual ds_boolean SerializeToString(std::string* buffer) = 0;

	// ����������������;
	virtual ds_uint32 ByteSize(void) = 0;

	// �Ƿ��б�Ҫ�ύ;
	virtual ds_boolean IsCommitNecessary(void) = 0;

	// �ύ����;
	virtual void Commit(std::function<void(ds_boolean)> func) = 0;

	// ɾ����Ǻ���;
	virtual void set_deleted(void) = 0;

	// ���ö�����;
	virtual void InitCommitObject(DatabaseCustomType dest_type, const char* dest_id, DatabaseCommitStatus commit_status) = 0;
};

/*
 *	���Ʊ�����;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomTable
{
public:
	virtual ~CDatabaseCustomTable(void) {}

	DS_PROPERTY(CDatabaseTableInfo, table);
};

/*
 *	���ƻ���;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomEnv
{
public:
	CDatabaseCustomEnv(void);
	~CDatabaseCustomEnv(void);

	// ���ݿ�ģʽ��ʼ��;
	ds_boolean InitSql(const std::string& com_id, const com::SqlConfig& sql_config, com::ITaskService::Ptr task_service);

	// ��ȡ���ݿ�����;
	com::ISqlConnector::Ptr GetSqlConnector(void);

	DS_SINGLETON(CDatabaseCustomEnv);

	DS_PROPERTY_PASS_BY_REF(std::string, com_id);
	DS_REF_PROPERTY_READONLY(com::SqlConfig, sql_config);
	DS_PROPERTY_READONLY(com::ITaskService::Ptr, task_service);
	DS_REF_PROPERTY(boost::thread_specific_ptr<com::ISqlConnector::Ptr>, sql_connector_tls);
};

NS_DS_END

#define sDatabaseCustomEnv dios::CDatabaseCustomEnv::GetInstancePtr()

#endif
