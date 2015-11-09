#include "precompiled.h"

#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include "dios_util/util_log.h"
#include "dios_util/util_rapidxml.h"
#include "dios_db_table/dios_db_tableinfo.h"
#include "dios_db_table/dios_db_tableinfo_loader.h"

#include "database_define_custom.h"
#include "database_common_custom.h"
#include "database_sql_custom.h"

#define DATABASE_CUSTOMC_VERSION "2015110601"

static ds_boolean WriteFile( const std::string& tableinfo_file, const std::string& output_path )
{
	// �������м��ر���Ϣ;
	auto table_info = sDatabaseTableInfoLoader->LoadTableInfoFromFile(tableinfo_file);
	if(!table_info) {
		return false;
	}

	// ���ɱ���Ϣ��MD5;
	std::string md5 = table_info->CalcMD5();

	// ��ȡĿ��Ŀ¼���Ƿ���${table_name}.cache�ļ�����;
	char cache_config_file[256];
	sprintf(cache_config_file, "%s/%s.cache", output_path.c_str(), table_info->name().c_str());

	// �ж��Ƿ���Ҫ���µ���;
	ds_boolean file_changed = true;
	try {

		// ��������;
		rapidxml::file<> fdoc(cache_config_file);
		if(fdoc.data() != 0) {

			rapidxml::xml_document<> doc;
			doc.parse<0>(fdoc.data(), fdoc.size());

			std::string cache_version, cache_md5;
			cache_version = sRapidXML->GetValue(&doc, "Version", cache_version);
			cache_md5 = sRapidXML->GetValue<std::string>(&doc, "md5", cache_md5);
			if(cache_version == DATABASE_CUSTOMC_VERSION && cache_md5 == md5) {
				file_changed = false;
			}
		}
	}
	catch (...) {
	}

	if(file_changed) {

		// �����ļ�;
		DatabaseDefineCustom::WriteFile(output_path.c_str(), table_info, "DATABASE_CUSTOMC_DECL");
		DatabaseCommonCustom::WriteFile(output_path.c_str(), table_info);
		DatabaseSqlCustom::WriteFile(output_path.c_str(), table_info);

		// ���ɻ����ļ�;
		rapidxml::xml_document<> doc;
		sRapidXML->SetValue(&doc, "Version", DATABASE_CUSTOMC_VERSION);
		sRapidXML->GetValue<std::string>(&doc, "md5", md5);

		std::string text;    
		rapidxml::print(std::back_inserter(text), doc, 0);    
		std::ofstream out(cache_config_file);  
		out<<doc;

		printf("write file successful!");
	}
	else {
		printf("file has nothing to change.");
	}
	return true;
}

int main(int argc, char* argv[])
{
	// ����˵��;
	printf("command param: tableinfo_file output_path)\n");

	// ��ȡӦ�ó������;
	if(argc < 3) {
		printf("command param too less");
		return 1;
	}

	// ��д�ļ�;
	if(!WriteFile(argv[1], argv[2])) {
		return 1;
	}
	return 0;
}
