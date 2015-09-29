#include "precompiled.h"
#include "http.h"

#include "libcurl/curl.h"
#include "dios_util/util_log.h"

#define CURL_HELPER_BREAK_IF(cond) if(cond) break

// 填充内容;
static long _WriteContent( char* data, int size, int nmemb, std::string &content) {

	long sizes = size * nmemb;
	content.append(data, sizes); 
	return sizes;
}

// 初始化curl;
static bool _CurlInit( CURL* &curl, const char* url, std::string &content, char* error) {

	do {
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_URL, url)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _WriteContent)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L)!= CURLE_OK);
		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L)!= CURLE_OK);
// 		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str()) != CURLE_OK);
// 		CURL_HELPER_BREAK_IF(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist) != CURLE_OK);
		return true;
	} while (0);
	return false;
}

CHttpServiceImpl::CHttpServiceImpl( void )
{
	CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (code != CURLE_OK) {
		sLogError("Failed to global init default [%d]\n", code);
	}
}

CHttpServiceImpl::~CHttpServiceImpl( void )
{
	curl_global_cleanup();
}

bool CHttpServiceImpl::GetUrlData( const std::string& url, std::string& content )
{
	CURL *curl = 0;
	CURLcode code;
	std::string http_content;
	char error[CURL_ERROR_SIZE];

	// 创建curl;
	curl = curl_easy_init();
	if (curl == 0) {
		sLogError("Failed to create CURL connection\n");
		return false;
	}

	// 初始化curl;
	if (!_CurlInit(curl, url.c_str(), http_content, error)) {
		sLogError("Failed to init curl\n");
		curl_easy_cleanup(curl);
		return false;
	}

	// 执行curl;
	code = curl_easy_perform(curl);
	if (code != CURLE_OK) {
		sLogError("Failed to get '%s' [%s]\n", url.c_str(), error);
		curl_easy_cleanup(curl);
		return false;
	}

	// 获取curl信息;
	long retcode = 0;
	bool return_code = false;
	code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &retcode); 
	if ( (code == CURLE_OK) && retcode == 200 ) {
		content = http_content;
		return_code = true;
	}
	else {
		sLogError("Failed to get '%s' [%d]", url.c_str(), retcode);
	}
	curl_easy_cleanup(curl);
	return return_code;
}