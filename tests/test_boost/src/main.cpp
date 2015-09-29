#include "precompiled.h"
#include <stdio.h>
#include "boost/thread.hpp"

int main(int argc, char **argv)
{

	boost::thread thread([](){ printf("hello thread\n"); });
	thread.join();
	printf("hello world\n");
}
