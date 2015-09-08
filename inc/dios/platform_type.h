

#ifndef __DIOS_PLATFORM_TYPE_H__
#define __DIOS_PLATFORM_TYPE_H__

#include <stdint.h>

typedef bool				ds_boolean;

typedef signed char			ds_int8;
typedef unsigned char		ds_uint8;
typedef short				ds_int16;
typedef unsigned short		ds_uint16;
typedef int					ds_int32;
typedef unsigned int		ds_uint32;
typedef long long			ds_int64;
typedef unsigned long long	ds_uint64;

typedef char				ds_char;
typedef wchar_t				ds_wchar;
typedef float				ds_float32;
typedef double				ds_float64;
typedef ds_uint8			ds_byte;


typedef unsigned char		ds_uchar;
typedef unsigned short		ds_ushort;
typedef unsigned int		ds_uint;
typedef unsigned long		ds_ulong;

typedef intptr_t			ds_intptr;

struct ds_point{
	int x;
	int y;
};


#endif  // __ds_PLATFORM_TYPE_H__