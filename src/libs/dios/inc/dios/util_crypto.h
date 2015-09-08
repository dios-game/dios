#ifndef __DIOS_UTIL_CRYPTO_H__
#define __DIOS_UTIL_CRYPTO_H__

#include "dios_util_lib.h"
#include <string>

NS_DIOS_BEGIN
NS_UTIL_BEGIN

class DIOS_UTIL_DECL CCrypto{

public:
	// -----------------------------
	static dios_uint32 Crc32( const char* buffer, dios_uint32 size );
	static std::string Md5( const char* buffer, dios_uint32 size );
	static std::string Sha1( const char* buffer, dios_uint32 size );

	static dios_uint32 XXHash( const char* buffer, dios_uint32 size, dios_uint32 seed );

	static std::string EncryptXXTEA(const char* buffer, dios_uint32 size, const std::string& key);
	static std::string DecryptXXTEA(const char* buffer, dios_uint32 size, const std::string& key);

	static std::string EncryptBase64(const char* buffer, dios_uint32 size);
	static std::string DecryptBase64(const char* buffer, dios_uint32 size);

	static std::string EncryptXOR(const char* buffer, dios_uint32 size, const std::string& key);
	static std::string DecryptXOR(const char* buffer, dios_uint32 size, const std::string& key);

	static void EncryptXORSelf(char* buffer, dios_uint32 size, const std::string& key);
	static void DecryptXORSelf(char* buffer, dios_uint32 size, const std::string& key);

	// -----------------------------
	static dios_uint32 Crc32( const std::string& content );
	static std::string Md5( const std::string& content );
	static std::string Sha1( const std::string& content );

	static dios_uint32 XXHash( const std::string& content, dios_uint32 hash_type );

	static std::string EncryptXXTEA(const std::string& content, const std::string& key);
	static std::string DecryptXXTEA(const std::string& content, const std::string& key);

	static std::string EncryptBase64(const std::string& content);
	static std::string DecryptBase64(const std::string& content);

	static std::string EncryptXOR(const std::string& content, const std::string& key);
	static std::string DecryptXOR(const std::string& content, const std::string& key);
};

NS_UTIL_END
NS_DIOS_END

#endif