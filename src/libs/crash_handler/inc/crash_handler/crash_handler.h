#ifndef ___CRASH_HANDLER_H___
#define ___CRASH_HANDLER_H___

#include "crash_handler_lib.h"

class CRASH_HANDLER_DECL CMyCrash{

public:
	void DerefZeroCrash(int test_cnt);
	void DerefZeroCrash1(int test_cnt);
	void DerefZeroCrash2(int test_cnt);
	void DerefZeroCrash3(int test_cnt);
	void DerefZeroCrash4(int test_cnt);
	void DerefZeroCrash5(int test_cnt);

	void InvalidParamCrash(int test_cnt);
	void PureCallCrash(int test_cnt);

	static void Install( const char* dump_file );
};

#endif // MDZ_NET_SERVICE_LIB_H
