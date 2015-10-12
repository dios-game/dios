#include "precompiled.h"
#include <stdio.h>


extern void TestLog();
extern void TestNetwork();

int main(int argc, char **argv)
{
	TestLog();
	TestNetwork();
	printf("hello world\n");
}
