#ifndef CODE_FILE_H
#define CODE_FILE_H

#include <stdio.h>

class CCodeFile
{
public:
	CCodeFile(void);
	~CCodeFile(void);

	// 初始化;
	ds_boolean Init(const std::string& file_name);

	// 增减Tab;
	void IncreaseTab(void);
	void DecreaseTab(void);

	// 打印;
	void WriteWithTab(const char* format, ...);
	void Write(const char* format, ...);

	inline const std::string& tab_string(void) { return tab_string_; }

	// 创建函数;
	static std::shared_ptr<CCodeFile> Create(const std::string& file_name);

private:

	// 更新Tab字符串;
	void _UpdateTabString(void);

	FILE* file_;

	int tab_count_;
	std::string tab_string_;
};

#endif
