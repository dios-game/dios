#ifndef __DIOS_COM_H___
#define __DIOS_COM_H___

#include "dios_com_context.h"
#include "dios_com_interface.hpp"
#include "dios_com_factory.hpp"
#include "dios_com_macro.h"


/*
 �������;
 -----------------------------------
 1. ����������;
 1. ���ʽ��� ;
	1. ��̬�������������(`CComFactory::Ptr`);
	2. ��̬�������������(`CComFactory::Ptr`);
	3. ������������������(`CComFactory::Ptr`);
 2. �������;
 3. ����������ʵ�� ;
	1. �������ӿ�;
	2. ʵ������ӿ�;

 PS. ����ԭ��������⹦��̫��̫�̫࣬��Ĺ��ܽӿ�һ���Ӷ������õ�(�������������Ƴ����֮�๦��)���������¼򻯡���������ֻ�����˻�������������������������ȫ���ɵ�;

 #### ���ʽ���;

 PLUGIN_EXPORT(plugin_name){
	PLUGIN_EXPORT_COM("com1", CCom1)
	PLUGIN_EXPORT_COM("com2", CCom2)
	PLUGIN_EXPORT_COM("com3", CCom3)
 }

 #### �����������;

	REGISTER_COM(CCom1);
	REGISTER_COM_WITH_NAME("com1", CCom1);

 ### �������ӿ�;

 class ICom1 : public ICom {
 public:
	virtual bool Function1() = 0;
 };

 ### ʵ������ӿ�;

 class CCom1 : public ICom1 {
 public:
	virtual bool Function1() {}
 };	
 */
#endif // __DIOS_COM_H___
