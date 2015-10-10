#ifndef DIOS_UTIL_RANDOM_MAP_HPP
#define DIOS_UTIL_RANDOM_MAP_HPP

#include <map>
#include <vector>

#include "dios_util_lib.h"
#include "dios_util/util_random.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	随机表单，目前数值(Value)只支持智能指针;
 */
template<class Key, class Value>
class CRandomMap
{
public:
	CRandomMap(void) {}
	~CRandomMap(void) {}

	// 添加数值;
	void Add(Key key, Value value) {
		
		// 判断是否已经存在同键数值;
		auto iter = value_index_map_.find(key);
		if(iter != value_index_map_.end()) {
			return;
		}

		ds_uint32 index = -1;

		// 抽取空闲下标;
		if(free_value_index_list_.size() > 0) {
			index = free_value_index_list_.front();
			free_value_index_list_.pop_front();
		}

		// 无空闲下标;
		if(index == -1) {

			// 插入到队列的后排;
			value_vec_.push_back(value);
			index = value_vec_.size() - 1;
		}
		else {

			// 直接设置到对应的位置;
			value_vec_[index] = value;
		}
		value_index_map_.insert(std::make_pair(key, index));
	}

	// 移除数值;
	void Remove(Key key) {

		// 尝试查找是否已经存在该键值;
		auto iter = value_index_map_.find(key);
		if(iter == value_index_map_.end()) {
			return;
		}

		// 从表单中删除;
		ds_uint32 index = iter->second;
		free_value_index_list_.push_back(index);
		value_vec_[index].reset();
		value_index_map_.erase(iter);
	}

	// 随机抽取;
	void RandomFetch(ds_int32 random_seed, 
		ds_uint32 fetch_count, 
		std::function<ds_boolean(Value)> filter_function,
		std::list<Value>& list) {

		if(fetch_count <= 0 || value_index_map_.size() <= 0) {
			return;
		}

		// 库存不足则全部添加;
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
		// 库存中随机添加;
		else {

			// 构建随机对象;
			util::CRandom random;
			random.Init(random_seed);

			for(ds_int32 i=0; i<fetch_count; ++i) {

				// 随机开始;
				ds_uint32 random_index = static_cast<ds_uint32>(random.RandomInt32(0, value_vec_.size()-1));
				ds_uint32 pos_index = random_index;
				for(ds_int32 j=0; j<value_vec_.size(); ++j) {

					// 获取对象;
					Value value = value_vec_[pos_index];
					if(value) {

						// 判断对象是否存在;
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

					// 不存在对象更换另一种尝试;
					++pos_index;
					if(pos_index >= value_vec_.size()) {
						pos_index = 0;
					}

					// 判断是否已经轮转一圈;
					if(pos_index != random_index) {
						continue;
					}
					return;
				}
			}
		}
	}

	// 判断是否存在;
	Value Get(Key key) {

		Value value;
		auto iter = value_index_map_.find(key);
		if(iter != value_index_map_.end()) {

			ds_uint32 index = iter->second;
			value = value_vec_[index];
		}
		return value;
	}

	// 获取数量;
	ds_int32 GetCount(void) { return value_index_map_.size(); }

private:
	std::vector<Value> value_vec_; // 随机用数组;
	std::list<ds_uint32> free_value_index_list_; // 空闲数组下标列表;
	std::map<Key, ds_uint32> value_index_map_; //数组下标表;
};

NS_UTIL_END
NS_DS_END

#endif