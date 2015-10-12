#include "precompiled.h"
#include <stdio.h>

#include "component/com_log.h"
#include "dios_com/dios_com.h"


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

int main(int argc, char **argv)
{
	TestLog();
	printf("hello world\n");
}
