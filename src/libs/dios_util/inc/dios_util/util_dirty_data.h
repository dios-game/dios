/*
 *	����������;
		������������ʽ������Դ�����������ݺ󣬵�һ�α�����Ϊ������ݽ������浽�������б��С�
	�ⲿֻ��Ҫ�Ը��б���б��������Ϳ��ԣ������ñ�������������;
 *
 */
#ifndef __DS_UTIL_DIRTY_DATA_H__
#define __DS_UTIL_DIRTY_DATA_H__

#include "dios_util_lib.h"
#include <list>
#include "util_bit_array.h"

NS_DS_BEGIN
NS_UTIL_BEGIN


/// \brief �������б�;
/// 
/// ��ϸ˵��: ʵ�������ݵ����ü��������б��ȡ;

class DS_UTIL_DECL CDirtyData
{
public:
	CDirtyData(void);
	~CDirtyData(void);

	/// \brief ��ʼ��;
	void Resize(ds_uint32 size);
	/// \brief ����������;
	void SetDirty(ds_uint32 index);
	/// \brief ����������;
	bool GetDirty(ds_uint32 index);
	/// \brief �Ƿ����������;
	bool HasDirty(void);	
	/// \brief ����������;
	void ClearDirty(void);
	/// \brief ���������������б�;
	inline const std::list<ds_uint32>& dirty_index_list(void) { return dirty_index_list_; }
	/// \brief ��������;string format��size+data;
	void ParseFromString(const std::string& input);
	/// \brief �������ݵ��ַ���;
	bool SerializeToString(std::string* output);

	ds_uint32 size();
private:
	
	CBitArray dirty_;
	std::list<ds_uint32> dirty_index_list_;
};

NS_UTIL_END
NS_DS_END

#endif // __DS_UTIL_DIRTY_LIST_H__
