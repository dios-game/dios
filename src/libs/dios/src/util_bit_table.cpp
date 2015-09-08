
#include "precompiled.h"
#include "util_bit_table.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

// ------------
// CBitTable
CBitTable::CBitTable()
{
	row_size_ = 0;
	column_size_ = 0;
	byte_size_ = 0;
	data_ = 0;
}

CBitTable::CBitTable(dios_uint32 row_size, dios_uint32 column_size)
{
	dios_uint32 bit_size = row_size*column_size;
	if(bit_size==0){
		row_size_ = 0;
		column_size_ = 0;
		byte_size_ = 0;
		data_ = 0;
	}
	else{
		row_size_ = row_size;
		column_size_ = column_size;
		byte_size_ = (bit_size+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memset(data_, 0, byte_size_);
	}
}

CBitTable::~CBitTable()
{
	if(data_){
		free(data_);
	}
}

void CBitTable::Resize(dios_uint32 row_size, dios_uint32 column_size)
{
	dios_uint32 bit_size = row_size*column_size;
	if(bit_size==0){
		if(data_){
			free(data_);
		}
		row_size_ = 0;
		column_size_ = 0;
		byte_size_ = 0;
		data_ = 0;
		return;
	}

	dios_uint8* old_data = data_;
	int old_size = byte_size_;
	if(old_data){
		row_size_ = row_size;
		column_size_ = column_size;
		byte_size_ = (bit_size+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memcpy(data_, old_data, byte_size_>old_size?old_size:byte_size_);
		free(old_data);
	}
	else{
		row_size_ = row_size;
		column_size_ = column_size;
		byte_size_ = (bit_size+7)>>3;
		data_ = (dios_uint8*)malloc(byte_size_);
		memset(data_, 0, byte_size_);
	}
}

void CBitTable::Set(dios_uint32 row, dios_uint32 column, dios_boolean val)
{
	if(row>=row_size_){
		return;
	}
	if(column>=column_size_){
		return;
	}

	dios_uint32 index = row*column_size_+column;

	unsigned char u = (1 << 7) >> (index&7);
	if (val){
		data_[(index>>3)] |= u;
	}
	else{
		data_[(index>>3)] &= ~u;
	}
}

dios_boolean CBitTable::Get(dios_uint32 row, dios_uint32 column)
{
	if(row>row_size_){
		return false;
	}
	if(column>=column_size_){
		return false;
	}

	dios_uint32 index = row*column_size_+column;
	dios_uint8 u = (1 << 7) >> (index&7);
	dios_uint8 k = this->data_[(index>>3)];
	return ((k & u) != 0);
}

void CBitTable::Clear()
{
	memset( data_, 0, byte_size_ );
}

void CBitTable::ParseFromString(const std::string& input)
{
	const char* input_data = input.data();
	dios_uint32 row_size = *((dios_uint32*)input_data);
	input_data += sizeof(dios_uint32);
	dios_uint32 column_size = *((dios_uint32*)input_data);
	input_data += sizeof(dios_uint32);
	Resize( row_size, column_size );

	dios_uint32 input_size = input.size()-sizeof(dios_uint32)-sizeof(dios_uint32);
	memcpy( data_, input_data, byte_size_>input_size?input_size:byte_size_ );
}

bool CBitTable::SerializeToString(std::string* output)
{
	if(!output){
		return false;
	}
	output->resize(byte_size_ + sizeof(dios_uint32) + sizeof(dios_uint32));
	char* output_data = DIOS_STRING_PTR(output);
	*((dios_uint32*)output_data) = row_size_;
	output_data += sizeof(dios_uint32);
	*((dios_uint32*)output_data) = column_size_;
	output_data += sizeof(dios_uint32);
	memcpy( output_data, data_, byte_size_ );
	return true;
}

NS_UTIL_END
NS_DIOS_END
