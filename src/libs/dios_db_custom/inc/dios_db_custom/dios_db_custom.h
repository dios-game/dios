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

// 定制类型;
enum DatabaseCustomType
{
	kDatabaseCustomTypeNil,	// 未定制;
	kDatabaseCustomTypeSql,	// 数据库直接操作定制;

	kDatabaseCustomTypeMax,
};

/*
 *	定制记录基类;
 */
class CDatabaseCustomRecord
{
public:
	virtual ~CDatabaseCustomRecord(void) {}
	
	// 二进制流加载;
	virtual void ParseFromArray(const void* buffer, ds_uint32 size) = 0;
	virtual void ParseFromString(const std::string& buffer) = 0;

	// 二进制流导出;
	virtual ds_boolean SerializeToArray(void* buffer, ds_uint32& size) = 0;
	virtual ds_boolean SerializeToString(std::string* buffer) = 0;

	// 二进制流导出容量;
	virtual ds_uint32 ByteSize(void) = 0;

	// 是否有必要提交;
	virtual ds_boolean IsCommitNecessary(void) = 0;

	// 提交函数;
	virtual void Commit(std::function<void(ds_boolean)> func) = 0;

	// 删除标记函数;
	virtual void set_deleted(void) = 0;

	// 设置定向函数;
	virtual void InitCommitObject(DatabaseCustomType dest_type, const char* dest_id, DatabaseCommitStatus commit_status) = 0;
};

/*
 *	定制表单基类;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomTable
{
public:
	virtual ~CDatabaseCustomTable(void) {}

	DS_PROPERTY(CDatabaseTableInfo, table);
};

/*
 *	定制环境;
 */
class DIOS_DB_CUSTOM_DECL CDatabaseCustomEnv
{
public:
	CDatabaseCustomEnv(void);
	~CDatabaseCustomEnv(void);

	// 数据库模式初始化;
	ds_boolean InitSql(const std::string& com_id, const com::SqlConfig& sql_config, com::ITaskService::Ptr task_service);

	// 获取数据库连接;
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
