#include "precompiled.h"
#include "log_service_impl.h"
#include "log_impl.h"

using namespace log4cplus;
using namespace log4cplus::helpers;

CLogServiceImpl::CLogServiceImpl()
{
	configure_watch_dog_thread_ = 0;

	/*
	*	³õÊ¼»¯root;
	*/
	SharedAppenderPtr _append(new ConsoleAppender());
	_append->setName("root");
	_append->setLayout( std::auto_ptr<Layout>(new TTCCLayout(true)) );
	Logger::getRoot().addAppender(_append);
}

CLogServiceImpl::~CLogServiceImpl()
{
	Shutdown();
}

bool CLogServiceImpl::Initialize( const std::string& log_config )
{
	if(!log_config.empty() && !configure_watch_dog_thread_){

		configure_watch_dog_thread_ = new ConfigureAndWatchThread(log_config, 5 * 1000);
		return true;
	}

	return false;
}

void CLogServiceImpl::Shutdown( void )
{
	if(configure_watch_dog_thread_){
		delete configure_watch_dog_thread_;
		configure_watch_dog_thread_ = 0;
	}
}

dios::com::ILog::Ptr CLogServiceImpl::CreateLog( const std::string& log_name )
{
	return CLogImpl::Ptr(new CLogImpl(shared_from_this(), log_name));
}

void CLogServiceImpl::NDC_Push( const char* ndc, ... )
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

void CLogServiceImpl::NDC_Pop()
{
	log4cplus::getNDC().pop();
}


PLUGIN_EXPORT(log_log4cplus){
	PLUGIN_EXPORT_COM("log_log4cplus", CLogServiceImpl)
}
