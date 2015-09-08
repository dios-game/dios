#include "precompiled.h"
#include "util_serializer.h"

NS_DIOS_BEGIN
NS_UTIL_BEGIN

CSerializer::operator bool() const
{
	return !IsEmpty();
}

dios_boolean CSerializer::IsEmpty() const
{
	return !write_seeker_;
}

void CSerializer::ResetWrite(std::size_t pos/*=0*/)
{
	if (pos < byte_array_.size())
	{
		write_seeker_ = pos;
	}
}

void CSerializer::ResetRead(std::size_t pos/*=0*/)
{
	if (pos < byte_array_.size())
	{
		read_seeker_ = pos;
	}
}

void CSerializer::Reset()
{
	write_seeker_ = 0;
	read_seeker_ = 0;
}

void CSerializer::Clear()
{
	write_seeker_ = 0;
	read_seeker_ = 0;
	byte_array_ = CByteArray();
}

void CSerializer::SeekOffset(dios_int32 offset)
{
	dios_int32 pos = read_seeker_;
	pos += offset;
	if( pos < 0) {
		pos = 0;
	}
	if( pos > (dios_uint16)write_seeker_ ) {
		pos = write_seeker_;
	}
	read_seeker_ = pos;
}

CByteArray CSerializer::data_last_read() const
{
	return CByteArray(byte_array_, read_seeker_, write_seeker_-read_seeker_);
}

CByteArray CSerializer::data() const
{
	return CByteArray(byte_array_, 0, write_seeker_);
}

std::size_t CSerializer::max_size() const
{
	return byte_array_.size();
}

std::size_t CSerializer::seeker() const
{
	return read_seeker_;
}

std::size_t CSerializer::size() const
{
	return write_seeker_;
}

CSerializer& CSerializer::operator>>(std::vector<std::string>& out)
{
	ReadStrings(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector< CByteArray >& out)
{
	ReadStrings(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_boolean>& out)
{
	ReadBools(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_float64>& out)
{
	ReadDoubles(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_float32>& out)
{
	ReadFloats(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_uint64>& out)
{
	ReadUlongs(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_int64>& out)
{
	ReadLongs(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_uint32>& out)
{
	ReadUints(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_int32>& out)
{
	ReadInts(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_uint16>& out)
{
	ReadUshorts(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_int16>& out)
{
	ReadShorts(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_uint8>& out)
{
	ReadUbytes(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::vector<dios_int8>& out)
{
	ReadBytes(out);
	return *this;
}

CSerializer& CSerializer::operator>>(std::string& out)
{
	ReadString(out);
	return *this;
}

CSerializer& CSerializer::operator>>(CByteArray& out)
{
	ReadString(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_boolean& out)
{
	ReadBool(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_float64& out)
{
	ReadDouble(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_float32& out)
{
	ReadFloat(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_uint64& out)
{
	ReadUlong(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_int64& out)
{
	ReadLong(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_uint32& out)
{
	ReadUint(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_int32& out)
{
	ReadInt(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_uint16& out)
{
	ReadUshort(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_int16& out)
{
	ReadShort(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_uint8& out)
{
	ReadUbyte(out);
	return *this;
}

CSerializer& CSerializer::operator>>(dios_int8& out)
{
	ReadByte(out);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<std::string>& in)
{
	WriteStrings(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector< CByteArray >& in)
{
	WriteStrings(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const CSerializer& in)
{
	WriteSerializer(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_boolean>& in)
{
	WriteBools(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_float64>& in)
{
	WriteDoubles(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_float32>& in)
{
	WriteFloats(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_uint64>& in)
{
	WriteUlongs(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_int64>& in)
{
	WriteLongs(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_uint32>& in)
{
	WriteUints(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_int32>& in)
{
	WriteInts(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_uint16>& in)
{
	WriteUshorts(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_int16>& in)
{
	WriteShorts(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_uint8>& in)
{
	WriteUbytes(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::vector<dios_int8>& in)
{
	WriteBytes(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const std::string& in)
{
	WriteString(in);
	return *this;
}

CSerializer& CSerializer::operator<<(char* in)
{
	WriteString(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const char* in)
{
	WriteString(in);
	return *this;
}

CSerializer& CSerializer::operator<<(const CByteArray& in)
{
	WriteString(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_boolean in)
{
	WriteBool(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_float64 in)
{
	WriteDouble(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_float32 in)
{
	WriteFloat(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_uint64 in)
{
	WriteUlong(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_int64 in)
{
	WriteLong(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_uint32 in)
{
	WriteUint(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_int32 in)
{
	WriteInt(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_uint16 in)
{
	WriteUshort(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_int16 in)
{
	WriteShort(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_uint8 in)
{
	WriteUbyte(in);
	return *this;
}

CSerializer& CSerializer::operator<<(dios_int8 in)
{
	WriteByte(in);
	return *this;
}

void CSerializer::ReadStrings(std::vector<std::string>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_uint16) <= write_seeker_ - read_seeker_, "ReadStrings:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		std::string d;
		ReadString(d);
		out.push_back(d);
	}
}

void CSerializer::ReadStrings(std::vector< CByteArray >& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_uint16) <= write_seeker_ - read_seeker_, "ReadStrings:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		CByteArray d;
		ReadString(d);
		out.push_back(d);
	}
}

void CSerializer::WriteStrings(const std::vector<std::string>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++)
	{
		WriteString(in[i]);
	}
}

void CSerializer::WriteStrings(const std::vector< CByteArray >& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++)
	{
		WriteString(in[i]);
	}
}

void CSerializer::WriteSerializer(const CSerializer& in)
{
	CByteArray buff = in.data_last_read();
	Write( buff.ptr(), buff.size() );
}

void CSerializer::ReadBools(std::vector<dios_boolean>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int8) <= write_seeker_ - read_seeker_, "ReadBools:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_boolean d;
		ReadBool(d);
		out.push_back(d);
	}
}

void CSerializer::WriteBools(const std::vector<dios_boolean>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteBool(in[i]);
	}
}

void CSerializer::ReadDoubles(std::vector<dios_float64>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_float64) <= write_seeker_ - read_seeker_, "ReadDoubles:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_float64 d = 0;
		ReadDouble(d);
		out.push_back(d);
	}
}

void CSerializer::WriteDoubles(const std::vector<dios_float64>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteDouble(in[i]);
	}
}

void CSerializer::ReadFloats(std::vector<dios_float32>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_float32) <= write_seeker_ - read_seeker_, "ReadFloats:OutOfArrayRange");

	if (out.capacity() != size){	
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_float32 d = 0;
		ReadFloat(d);
		out.push_back(d);
	}
}

void CSerializer::WriteFloats(const std::vector<dios_float32>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteFloat(in[i]);
	}
}

void CSerializer::ReadUlongs(std::vector<dios_uint64>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int64) <= write_seeker_ - read_seeker_, "ReadUlongs:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_uint64 d = 0;
		ReadUlong(d);
		out.push_back(d);
	}
}

void CSerializer::WriteUlongs(const std::vector<dios_uint64>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteUlong(in[i]);
	}
}

void CSerializer::ReadLongs(std::vector<dios_int64>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int64) <= write_seeker_ - read_seeker_, "ReadLongs:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_int64 d = 0;
		ReadLong(d);
		out.push_back(d);
	}
}

void CSerializer::WriteLongs(const std::vector<dios_int64>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteLong(in[i]);
	}
}

void CSerializer::ReadUints(std::vector<dios_uint32>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int16) <= write_seeker_ - read_seeker_, "ReadUints:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_uint32 d = 0;
		ReadUint(d);
		out.push_back(d);
	}
}

void CSerializer::WriteUints(const std::vector<dios_uint32>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteUint(in[i]);
	}
}

void CSerializer::ReadInts(std::vector<dios_int32>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int32) <= write_seeker_ - read_seeker_, "ReadInts:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_int32 d = 0;
		ReadInt(d);
		out.push_back(d);
	}
}

void CSerializer::WriteInts(const std::vector<dios_int32>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteInt(in[i]);
	}
}

void CSerializer::ReadUshorts(std::vector<dios_uint16>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int16) <= write_seeker_ - read_seeker_, "ReadUshorts:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_uint16 d = 0;
		ReadUshort(d);
		out.push_back(d);
	}
}

void CSerializer::WriteUshorts(const std::vector<dios_uint16>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){

		WriteUshort(in[i]);
	}
}

void CSerializer::ReadShorts(std::vector<dios_int16>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){

		return;
	}

	sLogAssert(size*sizeof(dios_int16) <= write_seeker_ - read_seeker_, "ReadShorts:OutOfArrayRange");

	if (out.capacity() != size){

		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){

		dios_int16 d = 0;
		ReadShort(d);
		out.push_back(d);
	}
}

void CSerializer::WriteShorts(const std::vector<dios_int16>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){

		WriteShort(in[i]);
	}
}

void CSerializer::ReadUbytes(std::vector<dios_uint8>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int8) <= write_seeker_ - read_seeker_, "ReadBytes:OutOfArrayRange");
	if (out.capacity() != size){			
		out.reserve(size);
		out.resize(0);
	}
	for (std::size_t i=0; i<size; ++i){
		dios_uint8 d = 0;
		ReadUbyte(d);
		out.push_back(d);
	}
}

void CSerializer::WriteUbytes(const std::vector<dios_uint8>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteUbyte(in[i]);
	}
}

void CSerializer::ReadBytes(std::vector<dios_int8>& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}

	sLogAssert(size*sizeof(dios_int8) <= write_seeker_ - read_seeker_, "ReadBytes:OutOfArrayRange");

	if (out.capacity() != size){
		out.reserve(size);
		out.resize(0);
	}

	for (std::size_t i=0; i<size; ++i){
		dios_int8 d = 0;
		ReadByte(d);
		out.push_back(d);
	}
}

void CSerializer::WriteBytes(const std::vector<dios_int8>& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	for(int i=0; i<(dios_uint16)in.size(); i++){
		WriteByte(in[i]);
	}
}

void CSerializer::ReadString(std::string& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}
	sLogAssert(size <= write_seeker_ - read_seeker_, "ReadString:OutOfArrayRange");
	out.assign((const char*)byte_array_.ptr()+read_seeker_, (std::size_t)size);
	read_seeker_ += size;
}

void CSerializer::ReadString(CByteArray& out)
{
	dios_uint16 size = 0;
	ReadUshort(size);
	if (size == 0){
		return;
	}
	sLogAssert(size <= write_seeker_ - read_seeker_, "ReadString:OutOfArrayRange");
	CByteArray byte_array((dios_byte*)byte_array_.ptr(read_seeker_), (std::size_t)size);
	out = byte_array;
	read_seeker_ += size;
}

void CSerializer::WriteString(const std::string& in)
{
	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	Write(in.c_str(), size);
}

void CSerializer::WriteString(const char* in)
{
	if (!in){
		return;
	}
	dios_uint16 size = (dios_uint16)strlen(in);
	WriteUshort(size);
	Write(in, size);
}

void CSerializer::WriteString(const CByteArray& in)
{
	if (!in){
		return;
	}

	dios_uint16 size = (dios_uint16)in.size();
	WriteUshort(size);
	Write(in.ptr(), size);
}

void CSerializer::ReadBool(dios_boolean& out)
{
	dios_int8 bl = 0;
	ReadByte(bl);
	if (bl == 0){
		out = false;
	}
	else{

		out = true;
	}
}

void CSerializer::WriteBool(dios_boolean in)
{
	dios_int8 bl = 0;
	if (in){
		bl = 1;
	}
	WriteByte(bl);
}

void CSerializer::ReadDouble(dios_float64& out)
{
	Read(&out, sizeof(dios_float64));
	if (is_flip_){
		CEndianHelper::FlipDouble(&out);
	}
}

void CSerializer::WriteDouble(dios_float64 in)
{
	if (is_flip_){
		CEndianHelper::FlipDouble(&in);
	}
	Write(&in, sizeof(dios_float64));
}

void CSerializer::ReadFloat(dios_float32& out)
{
	Read(&out, sizeof(dios_float32));
	if (is_flip_){
		CEndianHelper::FlipFloat(&out);
	}
}

void CSerializer::WriteFloat(dios_float32 in)
{
	if (is_flip_){
		CEndianHelper::FlipFloat(&in);
	}
	Write(&in, sizeof(dios_float32));
}

void CSerializer::ReadUlong(dios_uint64& out)
{
	Read(&out, sizeof(dios_uint64));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_uint64));
	}
}

void CSerializer::WriteUlong(dios_uint64 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_uint64));
	}
	Write(&in, sizeof(dios_uint64));
}

void CSerializer::ReadLong(dios_int64& out)
{
	Read(&out, sizeof(dios_int64));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_int64));
	}
}

void CSerializer::WriteLong(dios_int64 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_int64));
	}
	Write(&in, sizeof(dios_int64));
}

void CSerializer::ReadUint(dios_uint32& out)
{
	Read(&out, sizeof(dios_uint32));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_uint32));
	}
}

void CSerializer::WriteUint(dios_uint32 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_uint32));
	}
	Write(&in, sizeof(dios_uint32));
}

void CSerializer::ReadInt(dios_int32& out)
{
	Read(&out, sizeof(dios_int32));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_int32));
	}
}

void CSerializer::WriteInt(dios_int32 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_int32));
	}
	Write(&in, sizeof(dios_int32));
}

void CSerializer::ReadUshort(dios_uint16& out)
{
	Read(&out, sizeof(dios_uint16));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_uint16));
	}
}

void CSerializer::WriteUshort(dios_uint16 in)
{
	if (is_flip_){

		CEndianHelper::FlipEndian(&in, sizeof(dios_uint16));
	}
	Write(&in, sizeof(dios_uint16));
}

void CSerializer::ReadShort(dios_int16& out)
{
	Read(&out, sizeof(dios_int16));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_int16));
	}
}

void CSerializer::WriteShort(dios_int16 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_int16));
	}
	Write(&in, sizeof(dios_int16));
}

void CSerializer::ReadUbyte(dios_uint8& out)
{
	Read(&out, sizeof(dios_uint8));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_uint8));
	}
}

void CSerializer::WriteUbyte(dios_uint8 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_uint8));
	}
	Write(&in, sizeof(dios_uint8));
}

void CSerializer::ReadByte(dios_int8& out)
{
	Read(&out, sizeof(dios_int8));
	if (is_flip_){
		CEndianHelper::FlipEndian(&out, sizeof(dios_int8));
	}
}

void CSerializer::WriteByte(dios_int8 in)
{
	if (is_flip_){
		CEndianHelper::FlipEndian(&in, sizeof(dios_int8));
	}
	Write(&in, sizeof(dios_int8));
}

void CSerializer::Read(void* out, std::size_t size)
{
	if (out == 0 || size == 0){

		return;
	}

	sLogAssert(size <= write_seeker_ - read_seeker_, "Read:OutOfArrayRange");
	memcpy(out, byte_array_.ptr(read_seeker_), size);
	read_seeker_ += size;
}

void CSerializer::Write(const void* in, std::size_t size)
{
	if (in == 0 || size == 0){

		return;
	}
	sLogAssert(write_seeker_ + size <= byte_array_.size(), "Write:OutOfArrayRange");
	memcpy((char*)byte_array_.ptr(write_seeker_), in, size);
	write_seeker_ += size;
}

dios_boolean CSerializer::SetByteArray(const CByteArray& byte_array, std::size_t data_size)
{
	if ( !byte_array ){
		return false;
	}

	if (byte_array.elem_size() != sizeof(char)){
		return false;
	}
	write_seeker_ = data_size;
	read_seeker_ = 0;
	byte_array_ = byte_array;
	return true;
}

dios_boolean CSerializer::SetByteArray(const CByteArray& byte_array)
{
	if (!byte_array){
		return false;
	}

	if (byte_array.elem_size() != sizeof(char)){
		return false;
	}

	write_seeker_ = 0;
	read_seeker_ = 0;
	byte_array_ = byte_array;
	return true;
}

CSerializer::~CSerializer()
{

}

CSerializer::CSerializer(const CByteArray& byte_array, std::size_t size, CEndianHelper::Endian endian/*=DEFALT_SERIALIZER_ENDIAN*/) : 
	write_seeker_(0),read_seeker_(0),is_flip_(IsFlip(endian))
{
	sLogAssert(byte_array, "byte_array can't be null");
	sLogAssert(byte_array.elem_size() == sizeof(char), "byte_array's elemSize not equal with sizeof(char)");
	write_seeker_ = size;
	byte_array_ = byte_array;
}

CSerializer::CSerializer(const CByteArray& byte_array, CEndianHelper::Endian endian/*=DEFALT_SERIALIZER_ENDIAN*/) : 
	write_seeker_(0),read_seeker_(0),is_flip_(IsFlip(endian))
{
	sLogAssert(byte_array, "byte_array can't be null");
	sLogAssert(byte_array.elem_size() == sizeof(char), "byte_array's elemSize not equal with sizeof(byte)");
	byte_array_ = byte_array;
}

CSerializer::CSerializer(CEndianHelper::Endian endian/*=DEFALT_SERIALIZER_ENDIAN*/) : write_seeker_(0),read_seeker_(0),is_flip_(IsFlip(endian))
{

}
NS_UTIL_END
NS_DIOS_END