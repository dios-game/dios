#ifndef __DS_UTIL_TIMER_H__
#define __DS_UTIL_TIMER_H__

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

class DS_UTIL_DECL CTime{
public:
	static ds_uint64 NowTime( void );
	static ds_uint64 ToTime( std::string date_time_string );
	static ds_int64 DiffTime( ds_uint64 time1, ds_uint64 time2 );

	static std::string ToTimeSpanString( ds_int64 time_span );
	static std::string ToDateTimeString( ds_uint64 time );
	static std::string ToTimeString( ds_uint64 time );
	static std::string ToDateString( ds_uint64 time );
};

NS_UTIL_END
NS_DS_END
#endif // __DS_TIMER_H__
