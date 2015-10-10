#include "precompiled.h"
#include "util_boost_tls_buffer.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

CTlsBuffer::CTlsBuffer( void )
{
	default_size_ = 0;
}

CTlsBuffer::CTlsBuffer( unsigned int default_size )
{
	default_size_ = default_size;
}

CTlsBuffer::~CTlsBuffer( void )
{

}

void CTlsBuffer::set_default_size( unsigned int default_size )
{
	default_size_ = default_size;
}

std::string* CTlsBuffer::GetBuffer( void )
{
	std::string* buffer = tls_buffer_.get();
	if(!buffer) {
		buffer = new std::string;
		buffer->resize(default_size_);
		tls_buffer_.reset(buffer);
	}
	return buffer;
}

char* CTlsBuffer::GetBuffer( unsigned int size )
{
	std::string* buffer = tls_buffer_.get();
	if(!buffer) {
		buffer = new std::string;
		buffer->resize(size > default_size_ ? size : default_size_);
		tls_buffer_.reset(buffer);
	}
	else {
		if(size > buffer->size()) {
			buffer->resize(size);
		}
	}
	return &(*buffer->begin());
}

NS_UTIL_BOOST_END
NS_DS_END
