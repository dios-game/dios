#ifndef __DS_UTIL_CRYPTO_H__
#define __DS_UTIL_CRYPTO_H__

#include "dios_util_lib.h"
#include <string>

NS_DS_BEGIN
NS_UTIL_BEGIN

class DS_UTIL_DECL CCrypto{

public:
	// -----------------------------
	static ds_uint32 Crc32( const char* buffer, ds_uint32 size );
	static std::string Md5( const char* buffer, ds_uint32 size );
	static std::string Sha1( const char* buffer, ds_uint32 size );

	static ds_uint32 XXHash( const char* buffer, ds_uint32 size, ds_uint32 seed );

	static std::string EncryptXXTEA(const char* buffer, ds_uint32 size, const std::string& key);
	static std::string DecryptXXTEA(const char* buffer, ds_uint32 size, const std::string& key);

	static std::string EncryptBase64(const char* buffer, ds_uint32 size);
	static std::string DecryptBase64(const char* buffer, ds_uint32 size);

	static std::string EncryptXOR(const char* buffer, ds_uint32 size, const std::string& key);
	static std::string DecryptXOR(const char* buffer, ds_uint32 size, const std::string& key);

	static void EncryptXORSelf(char* buffer, ds_uint32 size, const std::string& key);
	static void DecryptXORSelf(char* buffer, ds_uint32 size, const std::string& key);

	// -----------------------------
	static ds_uint32 Crc32( const std::string& content );
	static std::string Md5( const std::string& content );
	static std::string Sha1( const std::string& content );

	static ds_uint32 XXHash( const std::string& content, ds_uint32 hash_type );

	static std::string EncryptXXTEA(const std::string& content, const std::string& key);
	static std::string DecryptXXTEA(const std::string& content, const std::string& key);

	static std::string EncryptBase64(const std::string& content);
	static std::string DecryptBase64(const std::string& content);

	static std::string EncryptXOR(const std::string& content, const std::string& key);
	static std::string DecryptXOR(const std::string& content, const std::string& key);
};

NS_UTIL_END
NS_DS_END

#endif