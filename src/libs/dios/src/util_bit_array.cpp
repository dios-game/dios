
#include "precompiled.h"
#include "util_bit_array.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

CBitArray::CBitArray( dios_uint32 size )
{
	if(size==0){
		size_ = 0;
		byte_size_ = 0;
		data_ = 0;
	}
	else{
		size_ = size;
		byte_size_ = (size_+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memset(data_, 0, byte_size_);
	}
}

CBitArray::CBitArray()
{
	size_ = 0;
	byte_size_ = 0;
	data_ = 0;
}

CBitArray::~CBitArray()
{
	if(data_){
		free(data_);
	}
}

void CBitArray::Set( dios_uint32 index, dios_boolean val )
{
	if ((index<0) || (index>size_))
		return;

	unsigned char u = (1 << 7) >> (index&7);
	if (val){
		data_[(index>>3)] |= u;
	}
	else{
		data_[(index>>3)] &= ~u;
	}
}

dios_boolean CBitArray::Get( dios_uint32 index )
{
	if ((index < 0) || (index >= size_))
		return false;
	dios_uint8 u = (1 << 7) >> (index&7);
	dios_uint8 k = this->data_[(index>>3)];
	return ((k & u) != 0);
}

void CBitArray::Clear()
{
	memset( data_, 0, byte_size_ );
}

void CBitArray::ParseFromString( const std::string& input )
{
	const char* input_data = input.data();
	dios_uint32 bis_size = *((dios_uint32*)input_data);
	Resize( bis_size );
	input_data += sizeof(dios_uint32);

	dios_uint32 input_size = input.size()-sizeof(dios_uint32);
	memcpy( data_, input_data, byte_size_>input_size?input_size:byte_size_ );
}

bool CBitArray::SerializeToString( std::string* output )
{
	if(!output){
		return false;
	}
	output->resize(byte_size_ + sizeof(dios_uint32));
	char* output_data = DIOS_STRING_PTR(output);
	*((dios_uint32*)output_data) = size_;
	output_data += sizeof(dios_uint32);
	memcpy( output_data, data_, byte_size_ );
	return true;
}

void CBitArray::Resize( dios_uint32 size )
{
	if(size==0){
		if(data_){
			free(data_);
		}
		size_ = 0;
		byte_size_ = 0;
		data_ = 0;
		return;
	}

	dios_uint8* old_data = data_;
	int old_size = byte_size_;
	if(old_data){
		size_ = size;
		byte_size_ = (size_+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memcpy(data_, old_data, byte_size_>old_size?old_size:byte_size_);
		free(old_data);
	}
	else{
		size_ = size;
		byte_size_ = (size_+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memset(data_, 0, byte_size_);
	}
}

NS_UTIL_END
NS_DIOS_END
