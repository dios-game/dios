#include "precompiled.h"
#include <stdio.h>
#include "libfoo/util_bit_array.h"

int main(int argc, char **argv)
{
	CBitArray  bit_array;
	bit_array.Resize(11);
	bit_array.Set(10, true);
	std::string str;
	bit_array.SerializeToString(&str);
	printf("bit_array(10:%s)\n", bit_array.Get(10) ? "true" : "false");
	printf("bit_array(9:%s)\n", bit_array.Get(9) ? "true" : "false");
}
