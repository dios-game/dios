#include "precompiled.h"
#include "dios_xor.h"

unsigned char *
	ds_xor_encrypt( const unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len, ds_uint32 *ret_length )
{
	if( key_len==0 || data_len==0 ){
		return 0;
	}

	unsigned char* ret_data = (unsigned char*)malloc(data_len);
	const unsigned char* read_pos = data;
	unsigned char* write_pos = ret_data;
	ds_uint32 read_len = 0;
	ds_uint32 key_pos = 0;
	while( read_len<data_len ){
		*write_pos = *read_pos ^ key[key_pos];
		++ read_pos;
		++ read_len;
		++ key_pos;
		++ write_pos;
		if(key_pos>=key_len){
			key_pos = 0;
		}
	}

	*ret_length = data_len;
	return ret_data;
}

unsigned char *
	ds_xor_decrypt( const unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len, ds_uint32 *ret_length )
{
	if( key_len==0 || data_len==0 ){
		return 0;
	}

	unsigned char* ret_data = (unsigned char*)malloc(data_len);
	const unsigned char* read_pos = data;
	unsigned char* write_pos = ret_data;
	ds_uint32 read_len = 0;
	ds_uint32 key_pos = 0;
	while( read_len<data_len ){
		*write_pos = *read_pos ^ key[key_pos];
		++ read_pos;
		++ read_len;
		++ key_pos;
		++ write_pos;
		if(key_pos>=key_len){
			key_pos = 0;
		}
	}
	*ret_length = data_len;
	return ret_data;
}

void ds_xor_encrypt_self(unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len)
{
	if( key_len==0 || data_len==0 ){
		return;
	}

	unsigned char* read_pos = data;
	unsigned char* write_pos = data;
	ds_uint32 read_len = 0;
	ds_uint32 key_pos = 0;
	while( read_len<data_len ){
		*write_pos = *read_pos ^ key[key_pos];
		++ read_pos;
		++ read_len;
		++ key_pos;
		++ write_pos;
		if(key_pos>=key_len){
			key_pos = 0;
		}
	}
}

void ds_xor_decrypt_self(unsigned char *data, ds_uint32 data_len, const unsigned char *key, ds_uint32 key_len)
{
	if( key_len==0 || data_len==0 ){
		return;
	}

	unsigned char* read_pos = data;
	unsigned char* write_pos = data;
	ds_uint32 read_len = 0;
	ds_uint32 key_pos = 0;
	while( read_len<data_len ){
		*write_pos = *read_pos ^ key[key_pos];
		++ read_pos;
		++ read_len;
		++ key_pos;
		++ write_pos;
		if(key_pos>=key_len){
			key_pos = 0;
		}
	}
}
