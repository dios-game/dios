#include "precompiled.h"
#include <stdio.h>

#include "component/com_log.h"

void TestLog(){
	sComContext->LoadPlugin("log_log4cplus");
	dios::com::ILogContext::Ptr log_context = sComContext->CreateCom<dios::com::ILogContext>("log_log4cplus");

	if (log_context){
		log_context->Initialize("log.properties");
		dios::com::ILog::Ptr log = log_context->CreateLog("root");
		if (log){
			log->Info("my_log");
		}
	}
}
