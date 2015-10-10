#include "precompiled.h"
#include "util_boost_key_value.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN
dios::util_boost::CKeyValue::CKeyValue(void)
{

}

dios::util_boost::CKeyValue::CKeyValue(const CKeyValue& node)
{
	key_value_map_ = node.key_value_map_;
}

void dios::util_boost::CKeyValue::ParseFromString(const std::string& data)
{
	dios::util_boost::CToken token(data, ":; ");
	for (int i = 1; i < token.strings().size(); i += 2){
		Set(token.strings()[i - 1], token.strings()[i]);
	}
}

bool dios::util_boost::CKeyValue::SerializeToString(std::string* output)
{
	if (!output){
		return false;
	}

	auto itor = key_value_map_.begin();
	while (itor != key_value_map_.end()){
		output->append(itor->first + ":" + itor->second + ";");
		++itor;
	}
	return true;
}
NS_UTIL_BOOST_END
NS_DS_END