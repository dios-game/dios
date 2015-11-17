#ifndef CODE_FILE_H
#define CODE_FILE_H

#include <stdio.h>

class CCodeFile
{
public:
	CCodeFile(void);
	~CCodeFile(void);

	// ��ʼ��;
	ds_boolean Init(const std::string& file_name);

	// ����Tab;
	void IncreaseTab(void);
	void DecreaseTab(void);

	// ��ӡ;
	void WriteWithTab(const char* format, ...);
	void Write(const char* format, ...);

	inline const std::string& tab_string(void) { return tab_string_; }

	// ��������;
	static std::shared_ptr<CCodeFile> Create(const std::string& file_name);

private:

	// ����Tab�ַ���;
	void _UpdateTabString(void);

	FILE* file_;

	int tab_count_;
	std::string tab_string_;
};

#endif
