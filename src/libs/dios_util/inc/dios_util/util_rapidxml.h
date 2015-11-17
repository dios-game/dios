#ifndef DIOS_UTIL_RAPIDXML_H
#define DIOS_UTIL_RAPIDXML_H

#include "dios_util_lib.h"

#include "dios/platform.h"
#include "dios_util/util_lexical_cast.hpp"
#include "rapidxml/rapidxml.hpp"

NS_DS_BEGIN
NS_UTIL_BEGIN

/*
 *	rapidxml����;
 */
class DS_UTIL_DECL CRapidXML
{
public:
	CRapidXML(void);
	~CRapidXML(void);

	// ��ȡ����;
	template<class T>
	T GetAttribute(const rapidxml::xml_node<>* xml_node, const std::string& key, T default_value) const {

		const char* value = _GetAttribute(xml_node, key);
		if(value == 0) {
			return default_value;
		}
		return dios::util::lexical_cast<T>(value);
	}

	bool GetAttribute(const rapidxml::xml_node<>* xml_node, const std::string& key, bool default_value) const {

		const char* value = _GetAttribute(xml_node, key);
		if(value == 0) {
			return default_value;
		}
		return (strcmp(value, "true") == 0 ? true : false);
	}

	// ��������;
	template<class T>
	void SetAttribute(rapidxml::xml_node<>* xml_node, const std::string& key, T value) {
		_SetAttribute(xml_node, key, dios::util::lexical_cast<std::string>(value));
	}

	void SetAttribute(rapidxml::xml_node<>* xml_node, const std::string& key, bool value) {
		_SetAttribute(xml_node, key, value ? "true" : "false");
	}

	// ��ȡ��ֵ;
	template<class T>
	T GetValue(const rapidxml::xml_node<>* xml_node, const std::string& key, T default_value) const {

		const char* value = _GetValue(xml_node, key);
		if(value == 0) {
			return default_value;
		}
		return dios::util::lexical_cast<T>(value);
	}

	bool GetValue(const rapidxml::xml_node<>* xml_node, const std::string& key, bool default_value) const {

		const char* value = _GetValue(xml_node, key);
		if(value == 0) {
			return default_value;
		}
		return (strcmp(value, "true") == 0 ? true : false);
	}

	// ������ֵ;
	template<class T>
	void SetValue(rapidxml::xml_node<>* xml_node, const std::string& key, T value) {
		_SetValue(xml_node, key, dios::util::lexical_cast<std::string>(value));
	}

	void SetValue(rapidxml::xml_node<>* xml_node, const std::string& key, bool value) {
		_SetValue(xml_node, key, value ? "true" : "false");
	}

	DS_SINGLETON(CRapidXML);

private:

	// ��ȡ����;
	const char* _GetAttribute(const rapidxml::xml_node<>* xml_node, const std::string& key) const {

		if(!xml_node) {
			return 0;
		}

		const rapidxml::xml_attribute<>* temp_node = xml_node->first_attribute(key.c_str());
		if(!temp_node || temp_node->value_size() == 0) {
			return 0;
		}
		return temp_node->value();
	}

	// ��������;
	void _SetAttribute(rapidxml::xml_node<>* xml_node, const std::string& key, const std::string& value) {

		if(!xml_node || !xml_node->document()) {
			return;
		}

		rapidxml::xml_attribute<>* temp_attribute = xml_node->document()->allocate_attribute(xml_node->document()->allocate_string(key.c_str()),
			xml_node->document()->allocate_string(value.c_str()));
		if(temp_attribute) {
			xml_node->append_attribute(temp_attribute);
		}
	}

	// ��ȡ��ֵ;
	const char* _GetValue(const rapidxml::xml_node<>* xml_node, const std::string& key) const {

		if(!xml_node) {
			return 0;
		}

		const rapidxml::xml_node<>* temp_node = xml_node->first_node(key.c_str());
		if(!temp_node || temp_node->value_size() == 0) {
			return 0;
		}
		return temp_node->value();
	}

	// ������ֵ;
	void _SetValue(rapidxml::xml_node<>* xml_node, const std::string& key, const std::string& value) {

		if(!xml_node || !xml_node->document()) {
			return;
		}

		rapidxml::xml_node<>* temp_node = xml_node->document()->allocate_node(rapidxml::node_element, 
			xml_node->document()->allocate_string(key.c_str()), 
			xml_node->document()->allocate_string(value.c_str()));
		if(temp_node) {
			xml_node->append_node(temp_node);
		}
	}
};

NS_UTIL_END
NS_DS_END

#define sRapidXML dios::util::CRapidXML::GetInstancePtr()

#endif
