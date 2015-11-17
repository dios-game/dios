#ifndef DIOS_COM_SQL_H
#define DIOS_COM_SQL_H

#include "dios/platform.h"

#include "component/com_log.h"
#include "dios_com/dios_com.h"

NS_DS_BEGIN

namespace com {

	// ��ѯ����ö��;
	enum SqlQueryError
	{
		SQL_QUERY_ERROR_OK,
		SQL_QUERY_ERROR_DISCONNECT,
		SQL_QUERY_ERROR_OTHER,
		SQL_QUERY_ERROR_MAX,
	};

	// �ֶ�����ö��;;
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
	 *	��ѯ�����;
	 */
	class ISqlResult
	{
	public:
		typedef std::shared_ptr<ISqlResult> Ptr;

		ISqlResult(void) {}
		virtual ~ISqlResult(void) {}

		// ��ȡ�ֶ�����;
		virtual ds_uint32 GetFieldCount(void) = 0;

		// ��ȡ�ֶ�����;
		virtual const char* GetFieldName(ds_uint32 field_index) = 0;

		// ���ݱ�Ż�ȡ�ֶ�����;
		virtual const char* GetFieldValueByIndex(ds_uint32 field_index, ds_uint32& size) = 0;

		// �������ƻ�ȡ�ֶ�����;;
		virtual const char* GetFieldValueByName(const std::string& field_name, ds_uint32& size) = 0;

		// ��ȡ��¼����;
		virtual ds_uint32 GetRowCount(void) = 0;

		// ����ɨ���¼;
		virtual ds_boolean FetchRow(void) = 0;
	};

	/*
	 *	���ݿ�����;
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
	 *	���ݿ�����;
	 */
	class ISqlConnector : public ICom
	{
	public:
		typedef std::shared_ptr<ISqlConnector> Ptr;

		// �������ݿ�;
		virtual ds_boolean Connect(const SqlConfig& config) = 0;

		// �ر����ݿ�����;
		virtual void Shutdown(void) = 0;

		// ִ�м����;
		virtual ISqlResult::Ptr ExecuteSql(const std::string& sql, SqlQueryError& error) = 0;

		// ִ�и�����䣬�����ı����;
		virtual ds_boolean ExecuteSqlBegin(const std::string& sql) = 0;

		// ִ�и�����䣬�����ֶ�����;
		virtual ds_boolean ExecuteSqlPushParam(SqlParamType database_param_type, const void* buffer, ds_uint32 size) = 0;

		// ִ�и�����䣬��ʽִ�в��õ����;
		virtual ds_boolean ExecuteSqlEnd(SqlQueryError& error) = 0;

		// ��ȡ�������;
		virtual ds_uint32 GetAutoIncrementID(void) = 0;
	};
}

NS_DS_END

#endif
