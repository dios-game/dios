#include "precompiled.h"
#include "util_time.h"
#include <math.h>

#include <iostream>
#include <ctime> 
#include <sstream>
#include <locale>
#include <iomanip>

#include "util_lexical_cast.hpp"

NS_DS_BEGIN
NS_UTIL_BEGIN
//-------------------------
//class: CTimeSpan
CTimeSpan::CTimeSpan()
{

}

CTimeSpan::CTimeSpan(int seconds, int minutes/*=0*/, int hours/*=0*/, int days/*=0*/) :duration_((days * 24 + hours)*3600+minutes*60+seconds)
{

}

CTimeSpan::CTimeSpan(const CTimeSpan& t)
{
	Reset(t);
}

CTimeSpan::~CTimeSpan()
{

}

void CTimeSpan::Reset(int seconds, int minutes/*=0*/, int hours/*=0*/, int days/*=0*/)
{
	duration_ = (days * 24 + hours) * 3600 + minutes * 60 + seconds;
}

void CTimeSpan::Reset(const CTimeSpan& t)
{
	duration_ = t.duration_;
}

ds_int32 CTimeSpan::GetSeconds()
{
	return duration_;
}

std::string CTimeSpan::ToString() const
{
	std::string time_span_string;
	ds_int32 total = duration_;
	ds_int32 seconds = total % 60;
	ds_int32 minutes = (total / 60) % 60;
	ds_int32 hours = total / 3600;

	if (hours<10){
		time_span_string += "0";
	}
	time_span_string += dios::util::lexical_cast<std::string>(hours);
	time_span_string += ":";
	if (minutes < 10){
		time_span_string += "0";
	}
	time_span_string += dios::util::lexical_cast<std::string>(minutes);
	time_span_string += ":";
	if (seconds < 10){
		time_span_string += "0";
	}
	time_span_string += dios::util::lexical_cast<std::string>(seconds);

	return time_span_string;
}

CTimeSpan CTimeSpan::operator+(CTimeSpan& time_span)
{
	CTimeSpan tReturn;
	tReturn.duration_ += time_span.duration_;
	return tReturn;
}

CTimeSpan CTimeSpan::operator-(CTimeSpan& time_span)
{
	CTimeSpan tReturn;
	tReturn.duration_ -= time_span.duration_;
	return tReturn;
}

bool CTimeSpan::operator>(const CTimeSpan& t) const
{
	return duration_ > t.duration_;
}

bool CTimeSpan::operator<(const CTimeSpan& t) const
{
	return duration_ < t.duration_;
}

bool CTimeSpan::operator>=(const CTimeSpan& t) const
{
	return duration_ >= t.duration_;
}

bool CTimeSpan::operator<=(const CTimeSpan& t) const
{
	return duration_ <= t.duration_;
}

bool CTimeSpan::operator==(const CTimeSpan& t) const
{
	return duration_ == t.duration_;
}

//-----------------
//class CTime

CTime::CTime()
{
	FromTimePoint(std::chrono::system_clock::now());
}

CTime::CTime(const std::string& time)
{
	FromString(time);
}

CTime::CTime(ds_int64 seconds_from_2012)
{
	FromSeconds(seconds_from_2012);
}										   

CTime::CTime(const CTime& t)
{
	Copy(t);
}

CTime::CTime(const std::chrono::system_clock::time_point& time)
{
	FromTimePoint(time);
}

CTime::~CTime(){}

//static
static std::time_t _GetTimePointFromString(const std::string& time_string){

	std::time_t time = 0;
	try	{
		std::tm tm_x = {};
		std::istringstream ss(time_string);
		// ss.imbue(std::locale("de_DE.utf-8"));
		ss >> std::get_time(&tm_x, "%Y-%m-%d %H:%M:%S");
		time = std::mktime(&tm_x);
	}
	catch (...){
		time = 0;
	}
	return time;
}

static ds_int64 _GetSecondsFrom2012(const std::time_t& time)
{
	auto time_2012 = _GetTimePointFromString(DS_TIME_STRING_2012);
	ds_int64 delta = time - time_2012;
	return delta;
}


CTime CTime::Now()
{
	CTime time(std::chrono::system_clock::now());
	return time;
}

void CTime::FromString(const std::string& time)
{
	try	{
		std::tm t = {};
		std::istringstream ss(time);
		// ss.imbue(std::locale("de_DE.utf-8"));
		ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
		std::time_t time_t_v = std::mktime(&t);
		FromCTime(time_t_v);
	}
	catch (...)	{
		FromTimePoint(std::chrono::system_clock::now());
	}
}

void CTime::FromCTime(const time_t& t)
{
	time_ = t;
	seconds_from_2012_ = _GetSecondsFrom2012(time_);
}

void CTime::FromTimePoint(const std::chrono::system_clock::time_point& t)
{
	FromCTime(std::chrono::system_clock::to_time_t(t));
}

void CTime::FromSeconds(ds_int64 seconds_from_2012)
{
	auto time_2012 = _GetTimePointFromString(DS_TIME_STRING_2012);
	FromCTime(time_2012 + seconds_from_2012);
}

void CTime::Copy(const CTime& t)
{
	time_ = t.time_;
	seconds_from_2012_ = t.seconds_from_2012_;
}

ds_uint32 CTime::GetSeconds(void) const
{
	return seconds_from_2012_;
}

void CTime::NextDays(int days/*=1*/, int hours/*=0*/)
{
	auto time = std::chrono::system_clock::from_time_t(time_);
	time += std::chrono::hours(24*days+hours);
	FromTimePoint(time);
}

bool			CTime::operator>	(const CTime& t) const { return time_ > t.time_; }
bool			CTime::operator<	(const CTime& t) const { return time_ < t.time_; }
bool			CTime::operator>=	(const CTime& t) const { return time_ >= t.time_; }
bool			CTime::operator<=	(const CTime& t) const { return time_ <= t.time_; }
bool			CTime::operator==	(const CTime& t) const { return time_ == t.time_; }
bool			CTime::operator!=	(const CTime& t) const { return time_ != t.time_; }
CTime			CTime::operator-	(const CTimeSpan& tSpan) const { CTime rtn(seconds_from_2012_ - tSpan.duration_); return rtn; }
CTimeSpan		CTime::operator-	(const CTime& t) const { CTimeSpan span; span.duration_ = time_ - t.time_; return span; }
CTime			CTime::operator+	(const CTimeSpan& tSpan) const { CTime rtn(seconds_from_2012_ + tSpan.duration_); return rtn; }
void			CTime::operator-=	(const CTimeSpan& tSpan) { time_ -= tSpan.duration_; seconds_from_2012_ = _GetSecondsFrom2012(time_); }
void			CTime::operator+=	(const CTimeSpan& tSpan) { time_ += tSpan.duration_; seconds_from_2012_ = _GetSecondsFrom2012(time_); }

//char*
bool			CTime::operator>	(const std::string& param) const { CTime time(param); return (*this)> time; }
bool			CTime::operator<	(const std::string& param) const { CTime time(param); return (*this)< time; }
bool			CTime::operator>=	(const std::string& param) const { CTime time(param); return (*this) >= time; }
bool			CTime::operator<=	(const std::string& param) const { CTime time(param); return (*this) <= time; }
bool			CTime::operator==	(const std::string& param) const { CTime time(param); return (*this) == time; }
CTimeSpan		CTime::operator-	(const std::string& param) const { CTime time(param); return (*this) - time; }

std::string CTime::ToString() const
{
	std::ostringstream ss;
	// ss.imbue(std::locale("de_DE.utf-8"));
	ss << std::put_time(std::localtime(&time_), "%Y-%m-%d %H:%M:%S");
	return ss.str();
}

std::string CTime::ToDateString() const
{
	std::ostringstream ss;
	// ss.imbue(std::locale("de_DE.utf-8"));
	ss << std::put_time(std::localtime(&time_), "%Y-%m-%d");
	return ss.str();
}

std::string CTime::ToTimeString() const
{
	std::ostringstream ss;
	// ss.imbue(std::locale("de_DE.utf-8"));
	ss << std::put_time(std::localtime(&time_), "%H:%M:%S");
	return ss.str();
}

NS_UTIL_END
NS_DS_END