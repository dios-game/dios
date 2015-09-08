#ifndef __DS_XOR_H__
#define __DS_XOR_H__
#include "dios/platform.h"

unsigned char *ds_xor_encrypt( const unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len, ds_uint32 *ret_length);
unsigned char *ds_xor_decrypt( const unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len, ds_uint32 *ret_length);

void ds_xor_encrypt_self( unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len);
void ds_xor_decrypt_self( unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len);

#endif /* __DS_XOR_H__ */
