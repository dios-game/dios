/************************************************************************/
/* 
	���ݿ������;
 */
/************************************************************************/

#ifndef DIOS_DB_TABLEINFO_H
#define DIOS_DB_TABLEINFO_H

#include "dios_db_table_lib.h"

#include <vector>
#include <string>

NS_DS_BEGIN

/*
 *	ö������;
 */
enum DatabaseColType
{
	DATABASE_COL_TYPE_NULL,
	DATABASE_COL_TYPE_SMALL_INT,				//	smallint;
	DATABASE_COL_TYPE_UNSIGNED_SMALL_INT,		//	word;
	DATABASE_COL_TYPE_INT,					//	int;
	DATABASE_COL_TYPE_UNSIGNED_INT,			//	dword;
	DATABASE_COL_TYPE_INT64,					//	int64;
	DATABASE_COL_TYPE_FLOAT,					//	float;
	DATABASE_COL_TYPE_STRING,					//	string;
	DATABASE_COL_TYPE_BLOB,					//	blob;
	DATABASE_COL_TYPE_UUID,					//	uuid;
	DATABASE_COL_TYPE_CHAR,					//	char;
	DATABASE_COL_TYPE_MAX,
};

class CDatabaseTableInfo;

/*
 *	�ֶ�����;
 */
class DIOS_DB_TABLE_DECL CDatabaseColInfo
{
public:

	friend class CDatabaseTableInfo;

	// �Ƚϲ���;
	ds_boolean operator==(const CDatabaseColInfo& col_info);
	ds_boolean operator!=(const CDatabaseColInfo& col_info);

	DS_PROPERTY_PASS_BY_REF(std::string, name); // �ֶ�����;
	DS_PROPERTY(DatabaseColType, type); // �ֶ�����;
	DS_PROPERTY(ds_uint32, char_size); // �ַ�����;
};

/*
 *	��������;
 */
class DIOS_DB_TABLE_DECL CDatabaseIndexInfo
{
public:

	friend class CDatabaseTableInfo;

	// �Ƚϲ���;
	ds_boolean operator==(const CDatabaseIndexInfo& index_info);
	ds_boolean operator!=(const CDatabaseIndexInfo& index_info);

	DS_PROPERTY_PASS_BY_REF(std::string, name); // ��������;
	DS_REF_PROPERTY(std::vector<std::string>, col_name_array); // �ֶ�����;
	DS_PROPERTY(ds_boolean, is_primary_key); // �Ƿ�����;
};

/*
 *	�������;
 */
class DIOS_DB_TABLE_DECL CDatabaseForeignKeyInfo
{
public:

	friend class CDatabaseTableInfo;

	// �Ƚϲ���;
	ds_boolean operator==(const CDatabaseForeignKeyInfo& foreign_key_info);
	ds_boolean operator!=(const CDatabaseForeignKeyInfo& foreign_key_info);

	DS_PROPERTY_PASS_BY_REF(std::string, name); // �������;
	DS_PROPERTY_PASS_BY_REF(std::string, col_name); // �ֶ�����;
	DS_PROPERTY_PASS_BY_REF(std::string, foreign_table_name); // �ⲿ������;
	DS_PROPERTY_PASS_BY_REF(std::string, foreign_col_name); // �ⲿ�ֶ�����;
};

/*
 *	���ݿ����Ϣ;
 */
class DIOS_DB_TABLE_DECL CDatabaseTableInfo
{
	typedef std::vector<CDatabaseColInfo> CDatabaseColInfoVector;
	typedef std::vector<CDatabaseIndexInfo> CDatabaseIndexInfoVector;
	typedef std::vector<CDatabaseForeignKeyInfo> CDatabaseForeignKeyInfoVector;

public:
	CDatabaseTableInfo(void);
	CDatabaseTableInfo(const std::string& name);
	CDatabaseTableInfo(const CDatabaseTableInfo& table_info);
	~CDatabaseTableInfo(void);

	// ��ֵ����;
	void operator=(const CDatabaseTableInfo& table_info);

	// �Ƚϲ���;
	ds_boolean operator==(const CDatabaseTableInfo& table_info);
	ds_boolean operator!=(const CDatabaseTableInfo& table_info);

	// ��ȡ����;
	CDatabaseIndexInfo GetPrimaryKey(void);

	// ��ȡMD5;
	std::string CalcMD5(void);

	DS_PROPERTY_PASS_BY_REF(std::string, name); // ����;
	DS_REF_PROPERTY(CDatabaseColInfoVector, col_info_vector); // �ֶ�����;
	DS_REF_PROPERTY(CDatabaseIndexInfoVector, index_info_vector); // �ֶ�����;
	DS_REF_PROPERTY(CDatabaseForeignKeyInfoVector, foreign_key_info_vector); // �ֶ�����;
};

NS_DS_END

#endif
