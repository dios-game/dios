#include "precompiled.h"
#include "dios_db_custom.h"

#include "dios_util/util_log.h"

NS_DS_BEGIN

CDatabaseCustomEnv::CDatabaseCustomEnv( void )
{

}

CDatabaseCustomEnv::~CDatabaseCustomEnv( void )
{

}

ds_boolean CDatabaseCustomEnv::InitSql( const std::string& com_id, const com::SqlConfig& sql_config, com::ITaskService::Ptr task_service )
{
	com_id_ = com_id;
	sql_config_ = sql_config;
	task_service_ = task_service;

	return true;
}

com::ISqlConnector::Ptr CDatabaseCustomEnv::GetSqlConnector( void )
{
	// TLS中获取数据库连接对象的指针;
	auto sql_connector = (com::ISqlConnector::Ptr*)sql_connector_tls_.get();
	if(!sql_connector) {

		// 新建指针;
		sql_connector = new com::ISqlConnector::Ptr;

		// 进行连接尝试;
		*sql_connector = sComContext->CreateCom<com::ISqlConnector>(com_id_.c_str());
		if(!*sql_connector) {
			delete sql_connector;

			sLogError("create sql connector failed!");
			return com::ISqlConnector::Ptr();
		}

		if(!(*sql_connector)->Connect(sql_config_)) {
			delete sql_connector;

			sLogError("Connect sql failed!");
			return com::ISqlConnector::Ptr();
		}

		// TLS设置成功
		sql_connector_tls_.reset(sql_connector);
	}
	return *sql_connector;
}


NS_DS_END