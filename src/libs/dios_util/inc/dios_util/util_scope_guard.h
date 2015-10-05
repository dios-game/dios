#ifndef __UTIL_SCOPE_GUARD_H___
#define __UTIL_SCOPE_GUARD_H___

#include "dios_util_lib.h"
#include "dios/platform.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	Bjarne Stroustrup��TC++PL���涨����`RAII��Resource Acquisition is Initialization��`��ʽ�������������ʱ�����������Դ��Ӧ���ڹ��캯���г�ʼ����������������ʱ�����ͷ���Щ��Դ��;
    Sample:
    void foo()
    {
       HANDLE h = CreateFile(...);
       DS_ON_SCOPE_EXIT { CloseHandle(h); }
       ... // use the file
    }
 *	Dismiss()����Ҳ��Andrei��ԭʼ��Ƶ�һ���֣���������Ϊ��֧��rollbackģʽ�����磺
	ScopeGuard onFailureRollback([&] { rollback; });
	... // do something that could fail
	onFailureRollback.Dismiss();
 */
class DS_UTIL_DECL CScopeGuard
{
public:
	explicit CScopeGuard(std::function<void()> onExitScope);
	~CScopeGuard();
	void Dismiss();
private:
	std::function<void()> on_exit_scope_;
	bool dismissed_;

private: // noncopyable;

	CScopeGuard(CScopeGuard const&);
	CScopeGuard& operator=(CScopeGuard const&);
};

NS_UTIL_END
NS_DS_END

#define _DS_SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define _DS_SCOPEGUARD_LINENAME(name, line) _DS_SCOPEGUARD_LINENAME_CAT(name, line)
#define DS_ON_SCOPE_EXIT(callback) dios::util::CScopeGuard _DS_SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

#endif
