#include "precompiled.h"
#include "util_scope_guard.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

void CScopeGuard::Dismiss()
{
	dismissed_ = true;
}

CScopeGuard::~CScopeGuard()
{
	if (!dismissed_)
	{
		on_exit_scope_();
	}
}

CScopeGuard::CScopeGuard(std::function<void()> onExitScope) : on_exit_scope_(onExitScope), dismissed_(false)
{

}


NS_UTIL_END
NS_DS_END
