#pragma once
#ifndef _DS_UTIL_SERIALIZER_H_
#define _DS_UTIL_SERIALIZER_H_

#include "dios_util_lib.h"

#include "dios/platform.h"
#include "util_endian.h"
#include "util_byte_array.h"

#include <vector>
#include <string>

NS_DS_BEGIN
NS_UTIL_BEGIN

#define THIS_IS_ENDIAN_LITTLE
#define DEFALT_SERIALIZER_ENDIAN CEndianHelper::ENDIAN_LITTLE

/// \brief 序列化类;
/// 
/// 详细说明：实现对缓冲区的序列化管理。写入通过size管理写入尾巴，读取通过seeker管理读取游标;
class DS_UTIL_DECL CSerializer
{
public:
	template<class T>
	void Serialize(CSerializer & serializer, T & in){
		void* buf = (void*)&in; serializer.Write(buf, sizeof(T));
	}

	template<class T>
	void Deserialize(CSerializer & serializer, T & out){
		void* buf = (void*)&out;  serializer.Read(buf, sizeof(T));
	}

	explicit CSerializer(CEndianHelper::Endian endian=DEFALT_SERIALIZER_ENDIAN);

	CSerializer(const CByteArray& byte_array, CEndianHelper::Endian endian=DEFALT_SERIALIZER_ENDIAN);
	CSerializer(const CByteArray& byte_array, std::size_t write_data_size, CEndianHelper::Endian endian=DEFALT_SERIALIZER_ENDIAN);
	~CSerializer();

public:
	ds_boolean SetByteArray(const CByteArray& byte_array);
	ds_boolean SetByteArray(const CByteArray& byte_array, std::size_t write_data_size);

	//----------------------------------------------------------------------------------------
	// void* 
	void Write(const void* in, std::size_t size);
	void Read(void* out, std::size_t size);

	//----------------------------------------------------------------------------------------
	/// ds_int8
	void WriteByte(ds_int8 in);
	CSerializer& operator<<(ds_int8 in);
	void ReadByte(ds_int8& out);
	CSerializer& operator>>(ds_int8& out);

	//----------------------------------------------------------------------------------------
	/// ds_uint8
	void WriteUbyte(ds_uint8 in);
	CSerializer& operator<<(ds_uint8 in);
	void ReadUbyte(ds_uint8& out);
	CSerializer& operator>>(ds_uint8& out);

	//----------------------------------------------------------------------------------------
	/// ds_int16
	void WriteShort(ds_int16 in);
	CSerializer& operator<<(ds_int16 in);
	void ReadShort(ds_int16& out);
	CSerializer& operator>>(ds_int16& out);

	//----------------------------------------------------------------------------------------
	/// ds_int32
	void WriteUshort(ds_uint16 in);
	CSerializer& operator<<(ds_uint16 in);
	void ReadUshort(ds_uint16& out);
	CSerializer& operator>>(ds_uint16& out);

	//----------------------------------------------------------------------------------------
	/// ds_int32
	void WriteInt(ds_int32 in);
	CSerializer& operator<<(ds_int32 in);
	void ReadInt(ds_int32& out);
	CSerializer& operator>>(ds_int32& out);

	//----------------------------------------------------------------------------------------
	/// ds_uint32
	void WriteUint(ds_uint32 in);
	CSerializer& operator<<(ds_uint32 in);
	void ReadUint(ds_uint32& out);
	CSerializer& operator>>(ds_uint32& out);

	//----------------------------------------------------------------------------------------
	/// ds_int64
	void WriteLong(ds_int64 in);
	CSerializer& operator<<(ds_int64 in);
	void ReadLong(ds_int64& out);
	CSerializer& operator>>(ds_int64& out);

	//----------------------------------------------------------------------------------------
	/// ds_uint64
	void WriteUlong(ds_uint64 in);
	CSerializer& operator<<(ds_uint64 in);
	void ReadUlong(ds_uint64& out);
	CSerializer& operator>>(ds_uint64& out);

	//----------------------------------------------------------------------------------------
	/// ds_float32
	void WriteFloat(ds_float32 in);
	CSerializer& operator<<(ds_float32 in);
	void ReadFloat(ds_float32& out);
	CSerializer& operator>>(ds_float32& out);

	//----------------------------------------------------------------------------------------
	/// ds_float64
	void WriteDouble(ds_float64 in);
	CSerializer& operator<<(ds_float64 in);
	void ReadDouble(ds_float64& out);
	CSerializer& operator>>(ds_float64& out);

	//----------------------------------------------------------------------------------------
	/// ds_boolean
	void WriteBool(ds_boolean in);
	CSerializer& operator<<(ds_boolean in);
	void ReadBool(ds_boolean& out);
	CSerializer& operator>>(ds_boolean& out);

	//----------------------------------------------------------------------------------------
	/// std::string
	void WriteString(const CByteArray& in);
	void WriteString(const char* in);
	void WriteString(const std::string& in);
	CSerializer& operator<<(const CByteArray& in);
	CSerializer& operator<<(const char* in);
	CSerializer& operator<<(char* in);
	CSerializer& operator<<(const std::string& in);

	void ReadString(CByteArray& out);
	void ReadString(std::string& out);
	CSerializer& operator>>(CByteArray& out);
	CSerializer& operator>>(std::string& out);

	//----------------------------------------------------------------------------------------
	/// bytes
	void WriteBytes(const std::vector<ds_int8>& in);
	CSerializer& operator<<(const std::vector<ds_int8>& in);
	void ReadBytes(std::vector<ds_int8>& out);
	CSerializer& operator>>(std::vector<ds_int8>& out);

	//----------------------------------------------------------------------------------------
	/// unsigned bytes
	void WriteUbytes(const std::vector<ds_uint8>& in);
	CSerializer& operator<<(const std::vector<ds_uint8>& in);
	void ReadUbytes(std::vector<ds_uint8>& out);
	CSerializer& operator>>(std::vector<ds_uint8>& out);

	//----------------------------------------------------------------------------------------
	/// shorts
	void WriteShorts(const std::vector<ds_int16>& in);
	CSerializer& operator<<(const std::vector<ds_int16>& in);
	void ReadShorts(std::vector<ds_int16>& out);
	CSerializer& operator>>(std::vector<ds_int16>& out);

	//----------------------------------------------------------------------------------------
	/// unsigned shorts
	void WriteUshorts(const std::vector<ds_uint16>& in);
	CSerializer& operator<<(const std::vector<ds_uint16>& in);
	void ReadUshorts(std::vector<ds_uint16>& out);
	CSerializer& operator>>(std::vector<ds_uint16>& out);

	//----------------------------------------------------------------------------------------
	/// ints;
	void WriteInts(const std::vector<ds_int32>& in);
	CSerializer& operator<<(const std::vector<ds_int32>& in);
	void ReadInts(std::vector<ds_int32>& out);
	CSerializer& operator>>(std::vector<ds_int32>& out);


	//----------------------------------------------------------------------------------------
	/// unsigned ints;
	void WriteUints(const std::vector<ds_uint32>& in);
	CSerializer& operator<<(const std::vector<ds_uint32>& in);
	void ReadUints(std::vector<ds_uint32>& out);
	CSerializer& operator>>(std::vector<ds_uint32>& out);

	//----------------------------------------------------------------------------------------
	/// longs
	void WriteLongs(const std::vector<ds_int64>& in);
	CSerializer& operator<<(const std::vector<ds_int64>& in);
	void ReadLongs(std::vector<ds_int64>& out);
	CSerializer& operator>>(std::vector<ds_int64>& out);

	//----------------------------------------------------------------------------------------
	/// unsigned longs
	void WriteUlongs(const std::vector<ds_uint64>& in);
	CSerializer& operator<<(const std::vector<ds_uint64>& in);
	void ReadUlongs(std::vector<ds_uint64>& out);
	CSerializer& operator>>(std::vector<ds_uint64>& out);

	//----------------------------------------------------------------------------------------
	/// floats
	void WriteFloats(const std::vector<ds_float32>& in);
	CSerializer& operator<<(const std::vector<ds_float32>& in);
	void ReadFloats(std::vector<ds_float32>& out);
	CSerializer& operator>>(std::vector<ds_float32>& out);

	//----------------------------------------------------------------------------------------
	/// doubles
	void WriteDoubles(const std::vector<ds_float64>& in);
	CSerializer& operator<<(const std::vector<ds_float64>& in);
	void ReadDoubles(std::vector<ds_float64>& out);
	CSerializer& operator>>(std::vector<ds_float64>& out);

	//----------------------------------------------------------------------------------------
	/// Write booleans
	void WriteBools(const std::vector<ds_boolean>& in);
	CSerializer& operator<<(const std::vector<ds_boolean>& in);
	void ReadBools(std::vector<ds_boolean>& out);
	CSerializer& operator>>(std::vector<ds_boolean>& out);

	//----------------------------------------------------------------------------------------
	/// Write Serializer;
	void WriteSerializer(const CSerializer& in);
	CSerializer& operator<<(const CSerializer& in);

	//----------------------------------------------------------------------------------------
	/// Write strings
	void WriteStrings(const std::vector< CByteArray >& in);
	void WriteStrings(const std::vector<std::string>& in);
	CSerializer& operator<<(const std::vector< CByteArray >& in);
	CSerializer& operator<<(const std::vector<std::string>& in);

	/// Read strings
	void ReadStrings(std::vector< CByteArray >& out);
	void ReadStrings(std::vector<std::string>& out);
	CSerializer& operator>>(std::vector< CByteArray >& out);
	CSerializer& operator>>(std::vector<std::string>& out);

	template <typename T>
	void WriteObject(const T& in){ 
		Serialize(*this, in); 
	}
	template <typename T>
	CSerializer& operator<<(const T& in){
		WriteObject(in);
		return *this;
	}

	template <typename T>
	void ReadObject(T& out){ 
		Deserialize(*this, out); 
	}

	template <typename T>
	CSerializer& operator>>(T& out){
		ReadObject(out);
		return *this;
	}

	template <typename  T>
	void WriteObjects(const std::vector<T>& in){
		ds_uint16 size = (ds_uint16)in.size();
		WriteUshort(size);
		for(int i=0; i<(ds_uint16)in.size(); i++){
			WriteObject(in[i]);
		}
	}

	template <typename T>
	void ReadObjects(std::vector<T>& out){
		ds_uint16 size = 0;
		ReadUshort(size);
		if (size == 0){
			return;
		}

		if (out.capacity() != size){
			out.reserve(size);
			out.resize(0);
		}

		for (std::size_t i=0; i<size; ++i){
			T t;
			ReadObject(t);
			out.push_back(t);
		}
	}

public:
	std::size_t size() const;
	std::size_t seeker() const;
	std::size_t max_size() const;
	CByteArray data() const;
	CByteArray data_last_read() const;

	void SeekOffset(ds_int32 offset);
	/// clear data and Read and Write offset
	void Clear();
	/// reset Read and Write offset but not clear byte_array
	void Reset();
	/// reset Read offset
	void ResetRead(std::size_t pos=0);
	/// reset Write offset
	void ResetWrite(std::size_t pos=0);
	/// empty
	ds_boolean IsEmpty() const;
	/// operator bool
	operator bool() const;

private:
	ds_boolean IsFlip(CEndianHelper::Endian e) {
		switch (e){
		case CEndianHelper::ENDIAN_NATIVE: 
			is_flip_ = false; 
			break;
		case CEndianHelper::ENDIAN_BIG:{
#ifdef THIS_IS_ENDIAN_LITTLE
			return true;
#else
			return false;
#endif
						}break;
		case CEndianHelper::ENDIAN_LITTLE:{
#ifdef THIS_IS_ENDIAN_LITTLE
			return false;
#else
			return true;
#endif
						   }break;
		}
		return false;
	}

private:
	std::size_t write_seeker_;
	std::size_t read_seeker_;
	ds_boolean is_flip_;
	CByteArray byte_array_;
};

NS_UTIL_END
NS_DS_END

#endif // _DS_UTIL_SERIALIZER_H_
