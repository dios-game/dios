#include "precompiled.h"

#include "dios/platform.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "dios_util/util_crypto.h"

extern void test_lua();
int main()
{
	std::cout<<"sizeof(void*) is:"<<(int)sizeof(intptr_t)<<std::endl;
	std::cout<<"sizeof(void*) is:"<<(int)sizeof(void*)<<std::endl;
	std::cout << "sizeof(xe_uint32) is:" << sizeof(ds_uint32) << std::endl;
	std::cout << "sizeof(xe_uint64) is:" << sizeof(ds_uint64) << std::endl;
	printf("hello world %s\n", dios::util::CCrypto::Md5("hello world").c_str());

	test_lua();
}
