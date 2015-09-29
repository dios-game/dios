#ifndef HTTP_SERVICE_IMPL_H
#define HTTP_SERVICE_IMPL_H


/*
 *	HTTP服务实现;
 */
class CHttpServiceImpl
{
public:
	CHttpServiceImpl(void);
	~CHttpServiceImpl(void);

	// 获取URL内容;
	bool GetUrlData(const std::string& url, std::string& content);
};

#endif