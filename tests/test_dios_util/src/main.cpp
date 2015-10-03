#include "precompiled.h"
#include <stdio.h>
#include <iostream>

#include "dios_util/util_bit_array.h"
#include "dios_util/util_bit_table.h"
#include "dios_util/util_dirty_data.h"
#include "dios_util/util_serializer.h"
#include "dios_util/util_crypto.h"
#include "dios_util/util_time.h"
#include "dios_util/util_timer.h"
#include "dios_util/util_batch_task_list.h"

#include "pthread.h"
#include <thread>

TEST(UtilTest, BitArrayTest)
{
	std::string out_string;

	// CBitArray;
	out_string="";
	dios::util::CBitArray bit_array;
	dios::util::CBitArray bit_array2;
	bit_array.Resize(10);
	bit_array.Set(1, true);
	bit_array.Set(3, true);
	bit_array.Set(5, true);
	bit_array.Set(10, true);
	bit_array.SerializeToString(&out_string);
	bit_array2.ParseFromString(out_string);

	EXPECT_EQ(true, bit_array.Get(1));
	EXPECT_EQ(true, bit_array2.Get(1));
	EXPECT_EQ(false, bit_array.Get(10));
	EXPECT_EQ(false, bit_array2.Get(10));
}

TEST(UtilTest, BitTableTest)
{
	std::string out_string;

	// CBitTable;
	out_string="";
	dios::util::CBitTable bit_table;
	dios::util::CBitTable bit_table2;
	bit_table.Resize(5,2);
	bit_table.Set(0, 1, true);
	bit_table.Set(1, 1, true);
	bit_table.Set(2, 1, true);
	bit_table.Set(2, 2, true);
	bit_table.SerializeToString(&out_string);
	bit_table2.ParseFromString(out_string);

	EXPECT_EQ(true, bit_table.Get(2,1));
	EXPECT_EQ(true, bit_table2.Get(2,1));
	EXPECT_EQ(false, bit_table.Get(2,2));
	EXPECT_EQ(false, bit_table2.Get(2,2));
}


TEST(UtilTest, DirtyDataTest)
{
	std::string out_string;

	// CBitArray;
	out_string="";
	dios::util::CDirtyData bit_array;
	dios::util::CDirtyData bit_array2;
	bit_array.Resize(10);
	bit_array.SetDirty(1);
	bit_array.SetDirty(2);
	bit_array.SetDirty(3);
	bit_array.SetDirty(4);
	bit_array.SerializeToString(&out_string);
	bit_array2.ParseFromString(out_string);

	EXPECT_EQ(true, bit_array.GetDirty(1));
	EXPECT_EQ(true, bit_array2.GetDirty(1));
	EXPECT_EQ(false, bit_array.GetDirty(5));
	EXPECT_EQ(false, bit_array2.GetDirty(5));
}


TEST(UtilTest, SerializerTest)
{
	char buff[1024] = {0};
	ds_byte one;
	ds_int32 two;
	std::string three;
	dios::util::CByteArray buffer(buff, 1024);
	dios::util::CSerializer serializer(buffer, 0);
	serializer.WriteByte(10);
	serializer<<10;
	serializer<<"xxxxx";
	serializer>>one>>two>>three;

	EXPECT_EQ(10, one);
	EXPECT_EQ(10, two);
	EXPECT_STREQ("xxxxx", three.c_str());
}

class CryptoTest:public testing::Test{

public:
	static void SetUpTestCase() {
		char list[] = "abcdefghijklmnopqrstuvwxyz";
		for(int i=0; i<data_size_; ++i){
			char temp[2] = {0};
			temp[0] = list[rand()%26];
			data_ += temp;
		}
	}

	static void TearDownTestCase() {

	}
	
	static std::string data_;
	int value_;
	std::string value_string_;
	static const int test_times_ = 1;
	static const int data_size_ = 1024*1024;
};

std::string CryptoTest::data_;

TEST_F(CryptoTest, Crc32){	
	for(int i=0; i<test_times_; ++i) value_ = dios::util::CCrypto::Crc32(data_);
	EXPECT_EQ(158520161, dios::util::CCrypto::Crc32("123456")); 
}
TEST_F(CryptoTest, Md5){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::Md5(data_);
	EXPECT_STREQ("e10adc3949ba59abbe56e057f20f883e", dios::util::CCrypto::Md5("123456").c_str()); 
}

TEST_F(CryptoTest, XXHash){	
	for(int i=0; i<test_times_; ++i) value_ = dios::util::CCrypto::XXHash(data_, 1);
	EXPECT_EQ(21462057, dios::util::CCrypto::XXHash("123456",1)); 
}
TEST_F(CryptoTest, EncryptBase64){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::EncryptBase64(data_);
	EXPECT_STREQ("MTIzNDU2", dios::util::CCrypto::EncryptBase64("123456").c_str()); 
}
TEST_F(CryptoTest, DecryptBase64){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::DecryptBase64(data_);
	EXPECT_STREQ("123456", dios::util::CCrypto::DecryptBase64("MTIzNDU2").c_str()); 
}
TEST_F(CryptoTest, EncryptXXTEA){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::EncryptXXTEA(data_, "zhangdong");
	EXPECT_STREQ("4+\x98\xE8k\xA2\xEC-X\x85\x84\xC1", dios::util::CCrypto::EncryptXXTEA("123456", "zhangdong").c_str()); 
}
TEST_F(CryptoTest, DecryptXXTEA){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::DecryptXXTEA("4+\x98\xE8k\xA2\xEC-X\x85\x84\xC1", "zhangdong");
	EXPECT_STREQ("123456", dios::util::CCrypto::DecryptXXTEA("4+\x98\xE8k\xA2\xEC-X\x85\x84\xC1", "zhangdong").c_str()); 
}
TEST_F(CryptoTest, EncryptXOR){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::EncryptXOR(data_, "zhangdong");
	EXPECT_STREQ("KZRZRR", dios::util::CCrypto::EncryptXOR("123456", "zhangdong").c_str()); 
}
TEST_F(CryptoTest, DecryptXOR){	
	for(int i=0; i<test_times_; ++i) value_string_ = dios::util::CCrypto::DecryptXOR(data_, "zhangdong");
	EXPECT_STREQ("123456", dios::util::CCrypto::DecryptXOR("KZRZRR", "zhangdong").c_str()); 
}

TEST(UtilTest, TimeTest1){

	// 字符串;
	dios::util::CTime string_time("2015-07-01 20:32:22");

	// 2012秒数;
	ds_uint64 stime = 110406742;
	dios::util::CTime second_time(stime);

	// 不常用的time_t;
	std::time_t ctime = 1435753942;
	dios::util::CTime c_time;
	c_time.FromCTime(ctime);

	EXPECT_STREQ("2015-07-01 20:32:22", string_time.ToString().c_str());
	EXPECT_STREQ("2015-07-01 20:32:22", second_time.ToString().c_str());
	EXPECT_STREQ("2015-07-01 20:32:22", c_time.ToString().c_str());
	EXPECT_STREQ("2015-07-01", string_time.ToDateString().c_str());
	EXPECT_STREQ("20:32:22", string_time.ToTimeString().c_str());

	// 时间间隔;	
	dios::util::CTimeSpan time_span(1000);
	EXPECT_STREQ("00:16:40", time_span.ToString().c_str());

	time_span.Reset(60);
	auto last_time = second_time - time_span;
	EXPECT_STREQ("2015-07-01 20:31:22", last_time.ToString().c_str());

	auto time_span_x = second_time - "2015-07-01 20:31:22";
	EXPECT_STREQ("00:01:00", time_span_x.ToString().c_str());

	// 获取当前时间;
	dios::util::CTime now_1 = dios::util::CTime::Now();
	ds_uint64 now_1_time = now_1.GetSeconds();
}

TEST(UtilTest, BatchTaskListTest){

	dios::util::CBatchTaskList::Ptr batch_task_list(new dios::util::CBatchTaskList);
	for (int i = 0; i < 100; ++i){ 
		batch_task_list->PushTask([](dios::util::CBatchTaskList::Ptr list){
			list->AddUncompletedTaskRef();
			std::thread thread = std::thread([=](){
				list->ReleaseUncompletedTaskRef();
				// printf(">>>>>>>>>>>batch_task_list %d/%d\n", list->GetUncompletedTask(), list->GetTotalTask());
			});	
			thread.detach();
		});
	}

	batch_task_list->DoAllTask([batch_task_list](){
		// auto id = std::this_thread::get_id();
		// printf(">>>>>>>>>>>batch_task_list %d/%d\n", batch_task_list->GetUncompletedTask(), batch_task_list->GetTotalTask());
	});

	while (batch_task_list->GetUncompletedTask() != 0){
		DS_SLEEP(100);
	}

	EXPECT_EQ(batch_task_list->GetUncompletedTask(), 0);
}

void* thread_proc( void* param ){

	printf("hello thread\n");
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	pthread_create(&thread, 0, thread_proc, 0);
	pthread_join(thread, 0);

	printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	ds_int32 rlt = RUN_ALL_TESTS();
	system("pause");
	return rlt;
}
