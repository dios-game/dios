#ifndef __DIOS_UTIL_TIMER_H__
#define __DIOS_UTIL_TIMER_H__

#include "dios_util_lib.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

class DIOS_UTIL_DECL CTime{
public:
	static dios_uint64 NowTime( void );
	static dios_uint64 ToTime( std::string date_time_string );
	static dios_int64 DiffTime( dios_uint64 time1, dios_uint64 time2 );

	static std::string ToTimeSpanString( dios_int64 time_span );
	static std::string ToDateTimeString( dios_uint64 time );
	static std::string ToTimeString( dios_uint64 time );
	static std::string ToDateString( dios_uint64 time );
};

NS_UTIL_END
NS_DIOS_END
#endif // __DIOS_TIMER_H__
