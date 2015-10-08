#ifndef __DIOS_COM_H___
#define __DIOS_COM_H___

#include "dios_com_context.h"
#include "dios_com_interface.hpp"
#include "dios_com_factory.hpp"
#include "dios_com_macro.h"


/*
 组件功能;
 -----------------------------------
 1. 添加组件工厂;
 1. 插件式组件 ;
	1. 静态插件添加组件工厂(`CComFactory::Ptr`);
	2. 动态插件添加组件工厂(`CComFactory::Ptr`);
	3. 本工程内添加组件工厂(`CComFactory::Ptr`);
 2. 创建组件;
 3. 组件的设计与实现 ;
	1. 设计组件接口;
	2. 实现组件接口;

 PS. 由于原来的组件库功能太杂太多，太多的功能接口一辈子都不会用的(例如禁用组件，移除组件之类功能)，上诉做下简化。工厂操作只保留了基本的添加组件工厂，其他功能全部干掉;

 #### 插件式组件;

 PLUGIN_EXPORT(plugin_name){
	PLUGIN_EXPORT_COM("com1", CCom1)
	PLUGIN_EXPORT_COM("com2", CCom2)
	PLUGIN_EXPORT_COM("com3", CCom3)
 }

 #### 本工程内添件;

	REGISTER_COM(CCom1);
	REGISTER_COM_WITH_NAME("com1", CCom1);

 ### 设计组件接口;

 class ICom1 : public ICom {
 public:
	virtual bool Function1() = 0;
 };

 ### 实现组件接口;

 class CCom1 : public ICom1 {
 public:
	virtual bool Function1() {}
 };	
 */
#endif // __DIOS_COM_H___
