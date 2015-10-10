#ifndef __DIOS_UTIL_BOOST_UUID_FUNCTION_HPP___
#define __DIOS_UTIL_BOOST_UUID_FUNCTION_HPP___

#include <map>
#include <string>


#include "dios_util_boost_lib.h"
#include "dios_util/util_timer.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

template< class FunctionType >
class CUuidFunction
{
private:
	struct FunctionInfo{
		std::function<FunctionType> func;
		ds_uint32 timeTick;
	};

public:
	typedef std::map<boost::uuids::uuid, FunctionInfo > FunctionMap;

	CUuidFunction( std::function<FunctionType> default_func ){
		default_func_ = default_func;
	}

	boost::uuids::uuid Create( std::function<FunctionType> func ) {
		static boost::uuids::random_generator uuid_gen;
		mutex_.lock();
		boost::uuids::uuid uuid = uuid_gen();
		function_map_[uuid].func = func;
		function_map_[uuid].timeTick = dios::util::CTimer::GetMilliSecond();
		mutex_.unlock();
		return uuid;
	}

	std::function<FunctionType> operator[]( const boost::uuids::uuid& func_id ) {

		std::function<FunctionType> func = default_func_;
		mutex_.lock();
		typename FunctionMap::iterator itor = function_map_.find(func_id);
		if(itor != function_map_.end()) {
			func = itor->second.func;
		}
		mutex_.unlock();
		return func;
	}

	std::function<FunctionType> operator[]( const std::string& func_id_str ) {

		static boost::uuids::string_generator uuid_gen;
		boost::uuids::uuid func_id = uuid_gen(func_id_str);
		return operator[](func_id);
	}

	std::function<FunctionType> Release(const boost::uuids::uuid& func_id) {

		std::function<FunctionType> func = default_func_;
		mutex_.lock();
		typename FunctionMap::iterator itor = function_map_.find(func_id);
		if(itor != function_map_.end()) {
			func = itor->second.func;
			function_map_.erase(itor);
		}
		mutex_.unlock();
		return func;
	}

	std::function<FunctionType> Release(const std::string& func_id_str) {

		static boost::uuids::string_generator uuid_gen;
		boost::uuids::uuid func_id = uuid_gen(func_id_str);
		return Release(func_id);
	}

	void GC( int time_expired_ms ){
		std::function<FunctionType> func;
		mutex_.lock();
		typename FunctionMap::iterator itor = function_map_.begin();
		ds_uint32 nowTick = dios::util::CTimer::GetMilliSecond();
		while(itor != function_map_.end()) {
			int delta = nowTick - itor->second.timeTick;
			if( delta >= time_expired_ms ){
				function_map_.erase(itor++);
			}
			else{
				++itor;
			}
		}
		mutex_.unlock();
	}

	std::function<FunctionType> ReleaseFront() {

		std::function<FunctionType> func = default_func_;
		mutex_.lock();
		typename FunctionMap::iterator itor = function_map_.begin();
		if(itor != function_map_.end()) {
			func = itor->second.func;
			function_map_.erase(itor);
		}
		mutex_.unlock();
		return func;
	}

	bool empty(){
		return function_map_.empty();
	}

private:
	FunctionMap function_map_;
	boost::mutex mutex_;
	std::function<FunctionType> default_func_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif