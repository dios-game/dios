#ifndef HTTP_SERVICE_IMPL_H
#define HTTP_SERVICE_IMPL_H


/*
 *	HTTP����ʵ��;
 */
class CHttpServiceImpl
{
public:
	CHttpServiceImpl(void);
	~CHttpServiceImpl(void);

	// ��ȡURL����;
	bool GetUrlData(const std::string& url, std::string& content);
};

#endif