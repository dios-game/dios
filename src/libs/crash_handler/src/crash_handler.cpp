#include "precompiled.h"
#include <stdio.h>
#include "google_breakpad/exception_handler.h"
#include "crash_handler.h"

#include "dios/platform.h"
#ifdef DS_PLATFORM_WIN32
#include <direct.h> 
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif


class Derived;

class Base {
public:
	Base(Derived* derived);
	virtual ~Base();
	virtual void DoSomething() = 0;

private:
	Derived* derived_;
};

class Derived : public Base {
public:
	Derived();
	~Derived();
	virtual void DoSomething();
};


Base::Base(Derived* derived)
	: derived_(derived) {
}

Base::~Base() 
{
	derived_->DoSomething();
}

#pragma warning(push)
#pragma warning(disable:4355)
// Disable warning C4355: 'this' : used in base member initializer list.
Derived::Derived()
	: Base(this) {  // C4355
}
#pragma warning(pop)

void Derived::DoSomething() {
	printf("Derived::DoSomething");
}

Derived::~Derived()
{

}

void CMyCrash::DerefZeroCrash(int test_cnt)
{
	if(--test_cnt==0){
		int* x = 0;
		*x = 1;
	}
	else{
		DerefZeroCrash(test_cnt);
	}
}

void CMyCrash::InvalidParamCrash(int test_cnt)
{
	if(--test_cnt==0){
		printf(0);
	}
	else{
		InvalidParamCrash(test_cnt);
	}
}

void CMyCrash::PureCallCrash( int test_cnt )
{
	if(--test_cnt==0){
		printf("Derived");
		Derived de;
		printf("~Derived");
	}
	else{
		PureCallCrash(test_cnt);
		return;
	}
	printf("exit PureCallCrash");
}

void CMyCrash::DerefZeroCrash1( int test_cnt )
{
	test_cnt++;
	DerefZeroCrash(test_cnt);
}

void CMyCrash::DerefZeroCrash2( int test_cnt )
{
	test_cnt-=3;
	DerefZeroCrash1(test_cnt);
}

void CMyCrash::DerefZeroCrash3( int test_cnt )
{
	test_cnt+=3;
	DerefZeroCrash2(test_cnt);
}

void CMyCrash::DerefZeroCrash4( int test_cnt )
{
	test_cnt-=5;
	DerefZeroCrash3(test_cnt);
}

void CMyCrash::DerefZeroCrash5( int test_cnt )
{
	test_cnt+=5;
	DerefZeroCrash4(test_cnt);
}

#ifdef DS_PLATFORM_WIN32

bool MakeDirectory( const char* dir_name )
{
	char	szNameBuff[256] = {0};
	strcpy(szNameBuff, dir_name);
	if(szNameBuff[strlen(szNameBuff)-1] != '\\') 
		szNameBuff[strlen(szNameBuff)]  = '\\';

	char	szBuff[256] = {0};
	char*	pos=strchr(szNameBuff, '\\');
	strncpy(szBuff, szNameBuff, pos-szNameBuff);
	do
	{
		if(pos != szNameBuff)// 开头不是'\\'
		{
			_mkdir( szBuff );
		}
		if(*(pos+1) == 0)// 到结尾了
			break;
		pos=strchr(pos+1, '\\');
		strncpy(szBuff, szNameBuff, pos-szNameBuff);
	}
	while(pos);
	return false;
}


static std::string ws2s(const std::wstring& ws)
{
	_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

static std::wstring s2ws(const std::string& s)
{
	_configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;

}

static bool callback(const wchar_t *dump_path, const wchar_t *id,
	void *context, EXCEPTION_POINTERS *exinfo,
	MDRawAssertionInfo *assertion,
	bool succeeded) 
{
	if (succeeded) {
		printf("dump guid is %ws\n", id);
	} else {
		printf("dump failed\n");
	}
	fflush(stdout);

	return succeeded;
}

#else

bool MakeDirectory( const char* dir_name )
{
	char	szNameBuff[256] = {0};
	strcpy(szNameBuff, dir_name);
	if(szNameBuff[strlen(szNameBuff)-1] != '/') 
		szNameBuff[strlen(szNameBuff)]  = '/';

	char	szBuff[256] = {0};
	char*	pos=strchr(szNameBuff, '/');
	strncpy(szBuff, szNameBuff, pos-szNameBuff);
	do
	{
		if(pos != szNameBuff)// 开头不是'/'
		{
			mkdir( szBuff, S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO );
		}
		if(*(pos+1) == 0)// 到结尾了
			break;
		pos=strchr(pos+1, '/');
		strncpy(szBuff, szNameBuff, pos-szNameBuff);
	}
	while(pos);
	return false;
}

static bool callback(const google_breakpad::MinidumpDescriptor& descriptor,
	void* context,
	bool succeeded)
{
	printf("Dump path: %s\n", descriptor.path());
	return succeeded;
}
#endif

void CMyCrash::Install( const char* dump_file )
{
	std::string floder = dump_file;
	MakeDirectory(floder.c_str());

#ifdef DS_PLATFORM_WIN32
	std::wstring w_floder = s2ws(floder);
	static google_breakpad::ExceptionHandler eh(
		w_floder.c_str(),
		NULL, 
		callback, 
		NULL,
		google_breakpad::ExceptionHandler::HANDLER_ALL);
#else
	google_breakpad::MinidumpDescriptor descriptor(floder);
	static google_breakpad::ExceptionHandler eh(descriptor,NULL, callback, NULL,true, -1);
#endif // DS_PLATFORM_WIN32
}
