#ifndef __DIOS_UTIL_BOOST_KEY_VALUE_HPP__
#define __DIOS_UTIL_BOOST_KEY_VALUE_HPP__

#include "dios_util_boost_lib.h"

#include <map>
#include <list>
#include <string>
#include "util_boost_token.hpp"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN
/*
 *	节点;
 */
class DIOS_UTIL_BOOST_DECL CKeyValue
{
public:
	CKeyValue(void);
	CKeyValue(const CKeyValue& node);

	void ParseFromString(const std::string& data);
	bool SerializeToString(std::string* output);

	// 获取子节点数值;
	template<class T>
	T Get(const std::string& key, T default_value) const {	   
		if (key_value_map_.size() == 0) {	
			return default_value;  
		} 
		auto itor = key_value_map_.find(key);
		if (itor != key_value_map_.end()){
			return boost::lexical_cast<T>(itor->second);
		}

		return default_value;
	}
	// 获取子节点数值;
	template<class T>
	void Set(const std::string& key, T value) {	
		key_value_map_.insert(std::make_pair(key, boost::lexical_cast<std::string>(value)));
	}
	// 获取子节点数值;
	template <>
	bool Get<ds_boolean>(const std::string& key, ds_boolean default_value) const{
		if (key_value_map_.size() == 0) {
			return default_value;
		}

		auto itor = key_value_map_.find(key);
		if (itor != key_value_map_.end()){
			return (strcmp(itor->second.c_str(), "true") == 0 ? true : false);
		}

		return default_value;
	}
	// 获取子节点数值;
	template <>
	void Set<ds_boolean>(const std::string& key, ds_boolean value){
		key_value_map_.insert(std::make_pair(key, value ? "true" : "false"));
	}
private:
	std::map<std::string, std::string> key_value_map_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif