#ifndef ___DIOS_UTIL_BOOST_TLS_BUFFER___
#define ___DIOS_UTIL_BOOST_TLS_BUFFER___


#include "dios_util_boost_lib.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

class DIOS_UTIL_BOOST_DECL CTlsBuffer
{
public:
	CTlsBuffer(void);
	CTlsBuffer(unsigned int default_size);
	~CTlsBuffer(void);

	// 设置默认缓存大小
	void set_default_size(unsigned int default_size);

	// 获取包缓存（默认/当前）
	std::string* GetBuffer(void);

	// 获取包缓存（动态）
	char* GetBuffer(unsigned int size);

private:

	// 默认缓存大小
	unsigned int default_size_;

	// TLS包缓存
	boost::thread_specific_ptr<std::string> tls_buffer_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif // ___DIOS_TLS_BUFFER___
