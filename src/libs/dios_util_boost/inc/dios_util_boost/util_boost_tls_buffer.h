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

	// ����Ĭ�ϻ����С
	void set_default_size(unsigned int default_size);

	// ��ȡ�����棨Ĭ��/��ǰ��
	std::string* GetBuffer(void);

	// ��ȡ�����棨��̬��
	char* GetBuffer(unsigned int size);

private:

	// Ĭ�ϻ����С
	unsigned int default_size_;

	// TLS������
	boost::thread_specific_ptr<std::string> tls_buffer_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif // ___DIOS_TLS_BUFFER___
