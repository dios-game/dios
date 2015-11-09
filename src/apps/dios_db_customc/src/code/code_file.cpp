#include "precompiled.h"
#include "code_file.h"

CCodeFile::CCodeFile( void )
{
	tab_count_ = 0;
	file_ = 0;
}

CCodeFile::~CCodeFile( void )
{
	if(file_) {
		fclose(file_);
		file_ = 0;
	}
}

bool CCodeFile::Init( const std::string& file_name )
{
	DS_ASSERT(file_ == 0, "file_ != 0? please run 'close' first!");
	if(file_) {
		return false;
	}

	tab_count_ = 0;
	file_ = fopen(file_name.c_str(), "wb");
	return (file_ != 0);
}

void CCodeFile::IncreaseTab( void )
{
	++tab_count_;
	_UpdateTabString();
}

void CCodeFile::DecreaseTab( void )
{
	DS_ASSERT(tab_count_ != 0, "tab_count_ == 0?");
	--tab_count_;
	_UpdateTabString();
}

void CCodeFile::WriteWithTab( const char* format, ... )
{
	DS_ASSERT(file_ != 0, "file_ == 0? please run 'open' first!");
	if(!file_) {
		return;
	}

	va_list args;
	va_start(args, format);

	std::string _format = tab_string_ + format;
	vfprintf(file_, _format.c_str(), args);
}

void CCodeFile::Write( const char* format, ... )
{
	DS_ASSERT(file_ != 0, "file_ == 0? please run 'open' first!");
	if(!file_) {
		return;
	}

	va_list args;
	va_start(args, format);

	vfprintf(file_, format, args);
}

void CCodeFile::_UpdateTabString( void )
{
	tab_string_.clear();

	//	tab_count
	for(int i=0; i<tab_count_; ++i) {
		tab_string_ += "	";
	}
}

std::shared_ptr<CCodeFile> CCodeFile::Create( const std::string& file_name )
{
	std::shared_ptr<CCodeFile> file(new CCodeFile);
	if(!file || !file->Init(file_name)) {
		return std::shared_ptr<CCodeFile>();
	}
	return file;
}
