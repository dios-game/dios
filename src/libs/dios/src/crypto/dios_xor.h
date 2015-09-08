#ifndef __DIOS_XOR_H__
#define __DIOS_XOR_H__
#include "dxm/platform.h"

unsigned char *dios_xor_encrypt( const unsigned char *data, dios_uint32 data_len, const unsigned char *key, dios_uint32 key_len, dios_uint32 *ret_length);
unsigned char *dios_xor_decrypt( const unsigned char *data, dios_uint32 data_len, const unsigned char *key, dios_uint32 key_len, dios_uint32 *ret_length);

void dios_xor_encrypt_self( unsigned char *data, dios_uint32 data_len, const unsigned char *key, dios_uint32 key_len);
void dios_xor_decrypt_self( unsigned char *data, dios_uint32 data_len, const unsigned char *key, dios_uint32 key_len);

#endif /* __DIOS_XOR_H__ */
