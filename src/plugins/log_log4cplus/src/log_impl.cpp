#include "precompiled.h"
#include "log_impl.h"

#ifdef DS_PLATFORM_WIN32
// ---- log4cplus 需要这个库;
#pragma comment(lib, "ws2_32.lib")
#endif

using namespace log4cplus;
using namespace log4cplus::helpers;

CLogImpl::CLogImpl( dios::ICom::Ptr component_depend, const std::string& log_config )
{
	if(!log_config.size() || log_config=="root")
	{	
		m_xLogger = Logger::getRoot();
	}
	else
	{
		m_xLogger = Logger::getInstance(log_config);
	}
}


CLogImpl::~CLogImpl()
{

}

void CLogImpl::Output( int level, const char* msg, ... )
{
	va_list args;
	va_start(args, msg);

	char buffer[4096];
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);

	switch(level)
	{
	case LOG_LEVEL_TRACE:
		_trace(buffer);
		break;
	case LOG_LEVEL_DEBUG:
		_debug(buffer);
		break;
	case LOG_LEVEL_INFO:
		_info(buffer);
		break;
	case LOG_LEVEL_WARN:
		_warn(buffer);
		break;
	case LOG_LEVEL_ERROR:
		_error(buffer);
		break;
	case LOG_LEVEL_FATAL:
		_fatal(buffer);
		break;
	}
}

void CLogImpl::Output( const char* msg, ... )
{
	va_list args;
	va_start(args, msg);

	char buffer[4096];
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);

	_info(buffer);
}

void CLogImpl::operator()( int level, const char* msg, ... )
{
	va_list args;
	va_start(args, msg);

	char buffer[4096];
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);

	switch(level)
	{
	case LOG_LEVEL_TRACE:
		_trace(buffer);
		break;
	case LOG_LEVEL_DEBUG:
		_debug(buffer);
		break;
	case LOG_LEVEL_INFO:
		_info(buffer);
		break;
	case LOG_LEVEL_WARN:
		_warn(buffer);
		break;
	case LOG_LEVEL_ERROR:
		_error(buffer);
		break;
	case LOG_LEVEL_FATAL:
		_fatal(buffer);
		break;
	}
}

void CLogImpl::operator()( const char* msg, ... )
{
	va_list args;
	va_start(args, msg);
	char buffer[4096];
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);

	_info(buffer);
}

void CLogImpl::NDC_Push( const char* ndc, ... )
{
	va_list args;
	va_start(args, ndc);
	char buffer[4096];
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, ndc, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, ndc, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);

	log4cplus::getNDC().push(buffer);
}

void CLogImpl::NDC_Pop()
{
	log4cplus::getNDC().pop();
}

void CLogImpl::Fatal( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_fatal(buffer);
}

void CLogImpl::Error( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_error(buffer);
}

void CLogImpl::Warn( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_warn(buffer);
}

void CLogImpl::Info( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_info(buffer);
}

void CLogImpl::Debug( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_debug(buffer);
}

void CLogImpl::Trace( const char* msg, ... )
{
	char buffer[4096];
	va_list args;
	va_start(args, msg);
	// MSVC 8 deprecates vsnprintf(), so we want to suppress warning
	// 4996 (deprecated function) there.
#ifdef DS_PLATFORM_WIN32  // We are on Windows.
#pragma warning(push)          // Saves the current warning state.
#pragma warning(disable:4996)  // Temporarily disables warning 4996.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#pragma warning(pop)           // Restores the warning state.
#else  // We are on Linux or Mac OS.
	const int size =
		vsnprintf(buffer, sizeof(buffer)/sizeof(buffer[0]) - 1, msg, args);
#endif  // GTEST_OS_WINDOWS
	va_end(args);
	_trace(buffer);
}


void CLogImpl::_fatal( const char* szMsg )
{
//	_SetColor(true, LMAGENTA);
	LOG4CPLUS_FATAL(m_xLogger, szMsg);
//	_SetColor(true, GREY);
}

void CLogImpl::_error( const char* szMsg )
{
//	_SetColor(true, LRED);
	LOG4CPLUS_ERROR(m_xLogger, szMsg);
//	_SetColor(true, GREY);
}

void CLogImpl::_warn( const char* szMsg )
{
//	_SetColor(true, YELLOW);
	LOG4CPLUS_WARN(m_xLogger, szMsg);
//	_SetColor(true, GREY);
}

void CLogImpl::_info( const char* szMsg )
{
//	_SetColor(true, GREY);
	LOG4CPLUS_INFO(m_xLogger, szMsg);
}

void CLogImpl::_debug( const char* szMsg )
{
//	_SetColor(true, LGREEN);
	LOG4CPLUS_DEBUG(m_xLogger, szMsg);
//	_SetColor(true, GREY);
}

void CLogImpl::_trace( const char* szMsg )
{
//	_SetColor(true, LCYAN);
	LOG4CPLUS_TRACE(m_xLogger, szMsg);
//	_SetColor(true, GREY);
}

void CLogImpl::_SetColor( bool stdout_stream, LogColor color )
{
#ifdef DS_PLATFORM_WIN32

	static WORD WinColorFG[COLOR_MAX] =
	{
		0,															// BLACK
		FOREGROUND_RED,												// RED
		FOREGROUND_GREEN,											// GREEN
		FOREGROUND_RED | FOREGROUND_GREEN,							// BROWN
		FOREGROUND_BLUE,											// BLUE
		FOREGROUND_RED | FOREGROUND_BLUE,							// MAGENTA
		FOREGROUND_GREEN | FOREGROUND_BLUE,							// CYAN
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,		// WHITE
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,	// YELLOW
		FOREGROUND_RED | FOREGROUND_INTENSITY,						// RED_BOLD
		FOREGROUND_GREEN | FOREGROUND_INTENSITY,					// GREEN_BOLD
		FOREGROUND_BLUE | FOREGROUND_INTENSITY,						// BLUE_BOLD
		FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,	// MAGENTA_BOLD
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,	// CYAN_BOLD
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY	// WHITE_BOLD
	};

	HANDLE hConsole = GetStdHandle(stdout_stream ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE );
	if(!hConsole) return;
	SetConsoleTextAttribute(hConsole, WinColorFG[color]);
#else

	enum ANSITextAttr
	{
		TA_NORMAL=0,
		TA_BOLD=1,
		TA_BLINK=5,
		TA_REVERSE=7
	};

	enum ANSIFgTextAttr
	{
		FG_BLACK=30, FG_RED,  FG_GREEN, FG_BROWN, FG_BLUE,
		FG_MAGENTA,  FG_CYAN, FG_WHITE, FG_YELLOW
	};

	enum ANSIBgTextAttr
	{
		BG_BLACK=40, BG_RED,  BG_GREEN, BG_BROWN, BG_BLUE,
		BG_MAGENTA,  BG_CYAN, BG_WHITE
	};

	static unsigned char UnixColorFG[COLOR_MAX] =
	{
		FG_BLACK,                                           // BLACK
		FG_RED,                                             // RED
		FG_GREEN,                                           // GREEN
		FG_BROWN,                                           // BROWN
		FG_BLUE,                                            // BLUE
		FG_MAGENTA,                                         // MAGENTA
		FG_CYAN,                                            // CYAN
		FG_WHITE,                                           // WHITE
		FG_YELLOW,                                          // YELLOW
		FG_RED,                                             // LRED
		FG_GREEN,                                           // LGREEN
		FG_BLUE,                                            // LBLUE
		FG_MAGENTA,                                         // LMAGENTA
		FG_CYAN,                                            // LCYAN
		FG_WHITE                                            // LWHITE
	};

	fprintf((stdout_stream? stdout : stderr), "\x1b[%s%dm", (color>=YELLOW&&color<COLOR_MAX ?";1":""), UnixColorFG[color]);
#endif

}
