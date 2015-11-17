#ifndef DIOS_COM_SQL_H
#define DIOS_COM_SQL_H

#include "dios/platform.h"

#include "component/com_log.h"
#include "dios_com/dios_com.h"

NS_DS_BEGIN

namespace com {

	// 查询错误枚举;
	enum SqlQueryError
	{
		SQL_QUERY_ERROR_OK,
		SQL_QUERY_ERROR_DISCONNECT,
		SQL_QUERY_ERROR_OTHER,
		SQL_QUERY_ERROR_MAX,
	};

	// 字段类型枚举;;
	enum SqlParamType
	{
		SQL_PARAM_TYPE_BYTE,
		SQL_PARAM_TYPE_SHORT,
		SQL_PARAM_TYPE_WORD,
		SQL_PARAM_TYPE_INT,
		SQL_PARAM_TYPE_DWORD,
		SQL_PARAM_TYPE_FLOAT,
		SQL_PARAM_TYPE_DOUBLE,
		SQL_PARAM_TYPE_STRING,
		SQL_PARAM_TYPE_BLOB,
		SQL_PARAM_TYPE_DATETIME,
		SQL_PARAM_TYPE_MAX,
	};

	/*
	 *	查询结果集;
	 */
	class ISqlResult
	{
	public:
		typedef std::shared_ptr<ISqlResult> Ptr;

		ISqlResult(void) {}
		virtual ~ISqlResult(void) {}

		// 获取字段数量;
		virtual ds_uint32 GetFieldCount(void) = 0;

		// 获取字段名称;
		virtual const char* GetFieldName(ds_uint32 field_index) = 0;

		// 根据编号获取字段内容;
		virtual const char* GetFieldValueByIndex(ds_uint32 field_index, ds_uint32& size) = 0;

		// 根据名称获取字段内容;;
		virtual const char* GetFieldValueByName(const std::string& field_name, ds_uint32& size) = 0;

		// 获取记录数量;
		virtual ds_uint32 GetRowCount(void) = 0;

		// 逐条扫描记录;
		virtual ds_boolean FetchRow(void) = 0;
	};

	/*
	 *	数据库配置;
	 */
	struct SqlConfig
	{
		std::string ip;
		ds_uint32 port;
		std::string id;
		std::string password;
		std::string db_name;
		std::string charset_name;
	};

	/*
	 *	数据库连接;
	 */
	class ISqlConnector : public ICom
	{
	public:
		typedef std::shared_ptr<ISqlConnector> Ptr;

		// 连接数据库;
		virtual ds_boolean Connect(const SqlConfig& config) = 0;

		// 关闭数据库连接;
		virtual void Shutdown(void) = 0;

		// 执行简单语句;
		virtual ISqlResult::Ptr ExecuteSql(const std::string& sql, SqlQueryError& error) = 0;

		// 执行复杂语句，输入文本语句;
		virtual ds_boolean ExecuteSqlBegin(const std::string& sql) = 0;

		// 执行复杂语句，推入字段内容;
		virtual ds_boolean ExecuteSqlPushParam(SqlParamType database_param_type, const void* buffer, ds_uint32 size) = 0;

		// 执行复杂语句，正式执行并得到结果;
		virtual ds_boolean ExecuteSqlEnd(SqlQueryError& error) = 0;

		// 获取自增编号;
		virtual ds_uint32 GetAutoIncrementID(void) = 0;
	};
}

NS_DS_END

#endif
