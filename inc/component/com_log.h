#ifndef _____COM_LOG_H_________
#define _____COM_LOG_H_________

#include "dios_com/dios_com.h"

namespace dios{
	namespace com{
		enum LogLevel{
			LOG_LEVEL_TRACE,  
			LOG_LEVEL_DEBUG,  
			LOG_LEVEL_INFO,  
			LOG_LEVEL_WARN,  
			LOG_LEVEL_ERROR, 
			LOG_LEVEL_FATAL,
		};

		class ILog
		{
		public:
			typedef std::shared_ptr<ILog> Ptr;
			ILog(){}
			virtual ~ILog( void ) {}

			/*
			 *	日志记录;
			 */
			virtual void Output(int level, const char* msg, ...) = 0;
			virtual void Output(const char* msg, ...) = 0; // level=LOG_LEVEL_INFO
			virtual void operator() (int level, const char* msg, ...) = 0;
			virtual void operator() (const char* msg, ...) = 0;	// level=LOG_LEVEL_INFO

			/*
			 *	nested diagnostic contexts
			 */
			virtual void NDC_Push(const char* ndc, ...) = 0;
			virtual void NDC_Pop() = 0;

			/*
			 *	具体输出函数;
			 */
			virtual void Fatal(const char* szMsg, ...) = 0;
			virtual void Error(const char* szMsg, ...) = 0;
			virtual void Warn (const char* szMsg, ...) = 0;
			virtual void Info (const char* szMsg, ...) = 0;
			virtual void Debug(const char* szMsg, ...) = 0;
			virtual void Trace(const char* szMsg, ...) = 0;
		};

		class ILogContext:public ICom
		{
		public:
			typedef std::shared_ptr<ILogContext> Ptr;

			virtual ~ILogContext(){}

			virtual bool Initialize( const std::string& log_config ) = 0;	
			virtual void Shutdown( void ) = 0;	
			virtual ILog::Ptr CreateLog( const std::string& log_name ) = 0;
			
			/*
			 *	nested diagnostic contexts
			 */
			virtual void NDC_Push(const char* ndc, ...) = 0;
			virtual void NDC_Pop() = 0;
		};
	}
}


#endif
