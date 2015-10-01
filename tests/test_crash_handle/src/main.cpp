#include "precompiled.h"
#include <stdio.h>

#include "crash_handler/crash_handler.h"


int main(int argc, char **argv)
{
	std::string dump_folder = "dump";
	std::string svn_version = "11";
	dump_folder += svn_version;	 
	CMyCrash::Install(dump_folder.c_str());

	int zero = 0;
	int div_zero = 10 / zero;
	printf("hello world %d\n", div_zero);
}
