#ifndef _DS_UTIL_ENDIAN_HELPER_H_
#define _DS_UTIL_ENDIAN_HELPER_H_

#include "dios_util_lib.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

class DS_UTIL_DECL CEndianHelper
{
public:
	// The endianness of written files;
	enum Endian
	{
		ENDIAN_NATIVE = 0, // Use the platform native endian;
		ENDIAN_BIG, // Use big endian (0x1000 is serialised as 0x10 0x00);
		ENDIAN_LITTLE // Use little endian (0x1000 is serialised as 0x00 0x10);
	};

	static void FlipEndian(void* data, int size);

	static float FlipFloat(float p);

	static double FlipDouble(double p);

	static void FlipFloat(float* p);

	static void FlipDouble(double* p);
};

NS_UTIL_END
NS_DS_END

#endif
