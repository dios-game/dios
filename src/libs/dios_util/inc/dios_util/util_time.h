#ifndef __UTIL_BOOST_TIME_H___
#define __UTIL_BOOST_TIME_H___

#include "dios_util_lib.h"
#include "dios/platform.h"

#include <chrono>
#include <ctime>

#define TIME_BUFF_SIZE 32

NS_DS_BEGIN
NS_UTIL_BEGIN

#define DS_TIME_STRING_2012 "2012-1-1 00:00:00"

enum TimePartName
{
	time_sec,
	time_min,
	time_hour,
	time_day,
	time_month,			// [0,11]
	time_year,			// 實際年份減去1900
	time_weekday,		// [0,6],0代表星期天,1代表星期一
	time_yeardays,		// [0,365],0代表1月1日,1代表1月2日	  
};

class CTime;
class DS_UTIL_DECL CTimeSpan
{
	friend		class CTime;
public:
	CTimeSpan();
	CTimeSpan(ds_int32 seconds, ds_int32 minutes = 0, ds_int32 hours = 0, ds_int32 days = 0);
	CTimeSpan(const CTimeSpan& t);
	~CTimeSpan();

	void Reset(ds_int32 seconds, ds_int32 minutes = 0, ds_int32 hours = 0, ds_int32 days = 0);
	void Reset(const CTimeSpan& t);

	ds_int32 GetSeconds();

	std::string ToString() const; // 获取当前时间标记HH:MM:SS;

	CTimeSpan operator+(CTimeSpan& time_span);
	CTimeSpan operator-(CTimeSpan& time_span);

	bool operator>(const CTimeSpan& t) const;
	bool operator<(const CTimeSpan& t) const;
	bool operator>=(const CTimeSpan& t) const;
	bool operator<=(const CTimeSpan& t) const;
	bool operator==(const CTimeSpan& t) const;

private:
	ds_int32 duration_;
};

class DS_UTIL_DECL CTime
{
public:
	static CTime  Now();

	CTime();
	CTime(const CTime& t);
	CTime(const std::string& time); // 2012-1-1 0:0:0 
	CTime(const std::time_t& tt);
	CTime(const std::chrono::system_clock::time_point& time);
	~CTime();

	void FromString(const std::string& time);
	void FromCTime(const std::time_t& tt);
	void FromTimePoint(const std::chrono::system_clock::time_point& time);
	void Copy(const CTime& t);

	std::string	ToString() const; // 获取当前日期标记YY-MM-DD HH:MM:SS; 
	std::string	ToDateString() const;  // 获取当前日期标记YY-MM-DD; 
	std::string	ToTimeString() const;  // 获取当前日期标记YY-MM-DD; 

	ds_uint32 GetSeconds(void) const;

	void NextWeek(int weekday = 0, int hours = 0);// next week day nHour:00:00 [0,6],0代表星期天,1代表星期一
	void NextDays(int days = 1, int hours = 0); // next nDay     00:00:00

	// ----Get Part of Time----
	bool			operator>	(const CTime& t) const;
	bool			operator<	(const CTime& t) const;
	bool			operator>=	(const CTime& t) const;
	bool			operator<=	(const CTime& t) const;
	bool			operator==	(const CTime& t) const;
	bool			operator!=	(const CTime& t) const;
	CTimeSpan		operator-	(const CTime& t) const;
	CTime			operator-	(const CTimeSpan& tSpan) const;
	CTime			operator+	(const CTimeSpan& tSpan) const;
	void			operator-=	(const CTimeSpan& tSpan);
	void			operator+=	(const CTimeSpan& tSpan);

	// string
	bool			operator>	(const std::string& time) const;
	bool			operator<	(const std::string& time) const;
	bool			operator>=	(const std::string& time) const;
	bool			operator<=	(const std::string& time) const;
	bool			operator==	(const std::string& time) const;
	CTimeSpan		operator-	(const std::string& time) const;

private:
	std::time_t time_;
};

NS_UTIL_END
NS_DS_END

/************************************************************************/
/*
_mktime32 returns the specified calendar time encoded as a value of type __time64_t.
If timeptr references a date before midnight, January 1, 1970, or if the calendar time
cannot be represented, _mktime32 returns –1 cast to type __time64_t.
When using _mktime32 and if timeptr references a date after 03:14:07 January 19, 2038,
Coordinated Universal Time (UTC),it will return –1 cast to type __time64_t.
_mktime64 will return –1 cast to type __time64_t if timeptr references a date after
23:59:59, December 31,3000, UTC.
*/

/*
32 1970 -- 2038-01-19 03:14:07
64 1970 -- 3000-12-31 23:59:59
*/

/************************************************************************/

#endif
