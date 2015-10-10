#ifndef DIOS_UTIL_RANDOM_MAP_HPP
#define DIOS_UTIL_RANDOM_MAP_HPP

#include <map>
#include <vector>

#include "dios_util_lib.h"
#include "dios_util/util_random.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	�������Ŀǰ��ֵ(Value)ֻ֧������ָ��;
 */
template<class Key, class Value>
class CRandomMap
{
public:
	CRandomMap(void) {}
	~CRandomMap(void) {}

	// �����ֵ;
	void Add(Key key, Value value) {
		
		// �ж��Ƿ��Ѿ�����ͬ����ֵ;
		auto iter = value_index_map_.find(key);
		if(iter != value_index_map_.end()) {
			return;
		}

		ds_uint32 index = -1;

		// ��ȡ�����±�;
		if(free_value_index_list_.size() > 0) {
			index = free_value_index_list_.front();
			free_value_index_list_.pop_front();
		}

		// �޿����±�;
		if(index == -1) {

			// ���뵽���еĺ���;
			value_vec_.push_back(value);
			index = value_vec_.size() - 1;
		}
		else {

			// ֱ�����õ���Ӧ��λ��;
			value_vec_[index] = value;
		}
		value_index_map_.insert(std::make_pair(key, index));
	}

	// �Ƴ���ֵ;
	void Remove(Key key) {

		// ���Բ����Ƿ��Ѿ����ڸü�ֵ;
		auto iter = value_index_map_.find(key);
		if(iter == value_index_map_.end()) {
			return;
		}

		// �ӱ���ɾ��;
		ds_uint32 index = iter->second;
		free_value_index_list_.push_back(index);
		value_vec_[index].reset();
		value_index_map_.erase(iter);
	}

	// �����ȡ;
	void RandomFetch(ds_int32 random_seed, 
		ds_uint32 fetch_count, 
		std::function<ds_boolean(Value)> filter_function,
		std::list<Value>& list) {

		if(fetch_count <= 0 || value_index_map_.size() <= 0) {
			return;
		}

		// ��治����ȫ�����;
		if(fetch_count >= value_index_map_.size()) {

			auto iter = value_index_map_.begin();
			while(iter != value_index_map_.end()) {

				ds_uint32 index = iter->second;
				Value value = value_vec_[index];
				if (!filter_function || filter_function(value)) {
					list.push_back(value);
				}
				++iter;
			}
		}
		// �����������;
		else {

			// �����������;
			util::CRandom random;
			random.Init(random_seed);

			for(ds_int32 i=0; i<fetch_count; ++i) {

				// �����ʼ;
				ds_uint32 random_index = static_cast<ds_uint32>(random.RandomInt32(0, value_vec_.size()-1));
				ds_uint32 pos_index = random_index;
				for(ds_int32 j=0; j<value_vec_.size(); ++j) {

					// ��ȡ����;
					Value value = value_vec_[pos_index];
					if(value) {

						// �ж϶����Ƿ����;
						ds_boolean is_already_exists = false;
						auto iter = list.begin();
						while(iter != list.end()) {

							Value temp_value = *iter;
							if(temp_value == value) {
								is_already_exists = true;
								break;
							}
							++iter;
						}
						if(!is_already_exists && !filter_function(value)) {
							list.push_back(value);
							break;
						}
					}

					// �����ڶ��������һ�ֳ���;
					++pos_index;
					if(pos_index >= value_vec_.size()) {
						pos_index = 0;
					}

					// �ж��Ƿ��Ѿ���תһȦ;
					if(pos_index != random_index) {
						continue;
					}
					return;
				}
			}
		}
	}

	// �ж��Ƿ����;
	Value Get(Key key) {

		Value value;
		auto iter = value_index_map_.find(key);
		if(iter != value_index_map_.end()) {

			ds_uint32 index = iter->second;
			value = value_vec_[index];
		}
		return value;
	}

	// ��ȡ����;
	ds_int32 GetCount(void) { return value_index_map_.size(); }

private:
	std::vector<Value> value_vec_; // ���������;
	std::list<ds_uint32> free_value_index_list_; // ���������±��б�;
	std::map<Key, ds_uint32> value_index_map_; //�����±��;
};

NS_UTIL_END
NS_DS_END

#endif