

#ifndef __DIOS_PLATFORM_TYPE_H__
#define __DIOS_PLATFORM_TYPE_H__

#include <stdint.h>

typedef bool				dios_boolean;

typedef signed char			dios_int8;
typedef unsigned char		dios_uint8;
typedef short				dios_int16;
typedef unsigned short		dios_uint16;
typedef int					dios_int32;
typedef unsigned int		dios_uint32;
typedef long long			dios_int64;
typedef unsigned long long	dios_uint64;

typedef char				dios_char;
typedef wchar_t				dios_wchar;
typedef float				dios_float32;
typedef double				dios_float64;
typedef dios_uint8			dios_byte;


typedef unsigned char		dios_uchar;
typedef unsigned short		dios_ushort;
typedef unsigned int		dios_uint;
typedef unsigned long		dios_ulong;

typedef intptr_t			dios_intptr;

struct dios_point{
	int x;
	int y;
};


#endif  // __DIOS_PLATFORM_TYPE_H__