#ifndef _____LOG_SERVICE_IMPL_H_________
#define _____LOG_SERVICE_IMPL_H_________

class CLogServiceImpl:public ILogContext
{
public:
	CLogServiceImpl();
	~CLogServiceImpl();

	virtual bool Initialize( const std::string& log_config );	
	virtual void Shutdown( void );	
	virtual dios::com::ILog::Ptr CreateLog( const std::string& log_name );

	virtual void NDC_Push(const char* ndc, ...);
	virtual void NDC_Pop();

private:
	log4cplus::ConfigureAndWatchThread* configure_watch_dog_thread_;
};


#endif