#ifndef _____LOG_IMPL_H_________
#define _____LOG_IMPL_H_________


enum LogColor
{
	BLACK,
	RED,
	GREEN,
	BROWN,
	BLUE,
	MAGENTA,
	CYAN,
	GREY,
	YELLOW,
	LRED,
	LGREEN,
	LBLUE,
	LMAGENTA,
	LCYAN,
	WHITE,
	COLOR_MAX,
};

class CLogImpl:public dios::log::ILog
{

public:
	typedef std::shared_ptr<CLogImpl> Ptr;

	CLogImpl(dios::ICom::Ptr component_depend, const std::string& log_config);
	~CLogImpl();

	/*
	*	日志记录;
	*/
	virtual void Output(int level, const char* msg, ...);
	virtual void Output(const char* msg, ...); // level=LOG_LEVEL_INFO
	virtual void operator() (int level, const char* msg, ...);
	virtual void operator() (const char* msg, ...);	// level=LOG_LEVEL_INFO

	virtual void NDC_Push(const char* ndc, ...);
	virtual void NDC_Pop();

	/*
	*	具体输出函数;
	*/
	virtual void Fatal(const char* szMsg, ...);
	virtual void Error(const char* szMsg, ...);
	virtual void Warn (const char* szMsg, ...);
	virtual void Info (const char* szMsg, ...);
	virtual void Debug(const char* szMsg, ...);
	virtual void Trace(const char* szMsg, ...);

private:
	void _fatal(const char* szMsg);
	void _error(const char* szMsg);
	void _warn (const char* szMsg);
	void _info (const char* szMsg);
	void _debug(const char* szMsg);
	void _trace(const char* szMsg);

	void _SetColor( bool stdout_stream, LogColor color );

	log4cplus::Logger  m_xLogger;
};

#endif