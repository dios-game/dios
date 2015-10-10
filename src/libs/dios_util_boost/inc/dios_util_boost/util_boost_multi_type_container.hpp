#ifndef __DIOS_UTIL_BOOST_MULTI_TYPE_CONTAINER___
#define __DIOS_UTIL_BOOST_MULTI_TYPE_CONTAINER___

#include <map>
#include <vector>


#include "dios_util_boost_lib.h"

/*
	目的:
		实现制作地图空间分区块管理地图实体对象(地图实体对象包含人物，怪物，宠物等)中区块存储地图实体的模块。
		一个方法是写一个地图实体的基类，然后根据类型放入不同的容器中。这个是拿到问题都会这么解决的通常做法。
		但是这样写出的代码是一次性的，跟我以前的项目一样的问题。
		另外一个办法就是模板咯。实现一个易于调整的容器。

	功能: 
		实现一个多类型的容器，实现指定类型的查找，添加，删除操作。

	使用:
		第一个模板参数表示存储的索引类型，例如人物，怪物等地图实体都是使用UUID进行管理的，那么使用如下
			CMultiTypeContainer<UUID, Player, Creature, OtherMapEntity ...>

	调整:
		当有新类型添加的时候只需要在模板参数后面添加类型即可。

	备注:
		被类型支持最多9中类型同时存储在一个容器中。
	
	例子:
	MiscHelper::CMultiTypeContainer<int, int, double, B> test_container;
	// 插入值
	test_container.insert<double>(0,11.0);
	test_container.insert<double>(0,10);
	test_container.insert<B>(0,B());
	// 插入智能指针
	std::shared_ptr<int> test_val_temp(new int(15));
	test_container.insert(1,test_val_temp);
	// 获取内容
	std::shared_ptr<int> test_val= test_container.find<int>(0);
	std::shared_ptr<double> test_val1 = test_container.find<double>(0);
	// 获取大小
	std::cout<<test_container.size<int>()<<"-"<<test_container.size<double>()<<endl;
	// 遍历
	test_container.visit<int>(std::bind(Test, _1));
	// 删除
	test_container.remove<int>(0);
		
 */
NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

class TypeNull;
template<typename HEAD, typename TAIL>
struct TypePair
{
	typedef HEAD Head;
	typedef TAIL Tail;
};

template<typename HEAD>
struct TypePair < HEAD, TypeNull >
{
	typedef HEAD Head;
	typedef TypeNull Tail;
};

template <class T0=TypeNull, class T1=TypeNull, class T2=TypeNull, class T3=TypeNull, class T4=TypeNull,
class T5=TypeNull, class T6=TypeNull, class T7=TypeNull, class T8=TypeNull, class T9=TypeNull>
struct TypeList
{
	typedef TypePair<T0,typename TypeList<T1, T2, T3, T4, T5,T6, T7, T8, T9, TypeNull>::type> type;
};

template <>
struct TypeList<TypeNull, TypeNull, TypeNull, TypeNull, TypeNull, TypeNull, TypeNull, TypeNull, TypeNull, TypeNull>
{
	typedef TypeNull type;
};

/*
*	单元容器
*/
template<class ContainerKey, class T> struct TypeContainers
{
	std::map<ContainerKey, T> objects;
};

template<class ContainerKey> struct TypeContainers<ContainerKey, TypeNull>
{
};

/*
*	复合容器
*/
template<class ContainerKey, class H, class T> struct TypeContainers< ContainerKey, TypePair<H, T> >
{
	TypeContainers<ContainerKey, H> head_container;
	TypeContainers<ContainerKey, T> tail_container;
};

template<	class ContainerKey,class T0=TypeNull, class T1=TypeNull, 
class T2=TypeNull, class T3=TypeNull, class T4=TypeNull,
class T5=TypeNull, class T6=TypeNull, class T7=TypeNull, 
class T8=TypeNull, class T9=TypeNull >
class CMultiTypeContainer
{
public:
	typedef TypeContainers<ContainerKey, typename TypeList<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>::type> CONTAINER;

	template < class SPECIFIC_TYPE> class iterator
	{
	public:
		typedef typename std::map<ContainerKey, SPECIFIC_TYPE>::iterator type;
	};
	/*
	*	获取SPECIFIC_TYPE类型容器大小
	*/
	template<class SPECIFIC_TYPE> 
	int size() { 
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return 0;
		}
		return elements->objects.size();
	}

	/*
	*	获取SPECIFIC_TYPE类型对象
	*/
	template<class SPECIFIC_TYPE> 
	typename iterator<SPECIFIC_TYPE>::type find(ContainerKey key) {
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return typename iterator<SPECIFIC_TYPE>::type();
		}
		return elements->objects.find(key);
	}

	template<class SPECIFIC_TYPE> 
	typename iterator<SPECIFIC_TYPE>::type begin() {
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return typename iterator<SPECIFIC_TYPE>::type();
		}
		return elements->objects.begin();
	}

	template<class SPECIFIC_TYPE> 
	typename iterator<SPECIFIC_TYPE>::type end() {
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return typename iterator<SPECIFIC_TYPE>::type();
		}
		return elements->objects.end();
	}

	/*
	*	插入SPECIFIC_TYPE类型对象
	*/
	template<class SPECIFIC_TYPE> bool insert(ContainerKey key, typename boost::call_traits<SPECIFIC_TYPE>::param_type obj) {
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return false;
		}
		typename iterator<SPECIFIC_TYPE>::type itor = elements->objects.find(key);
		if( itor != elements->objects.end()) {
			return false;
		}
		elements->objects[key] = obj;
		return true;
	}

	/*
	*	移除SPECIFIC_TYPE类型对象
	*/
	template<class SPECIFIC_TYPE> bool erase(ContainerKey key){
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return false;
		}
		typename iterator<SPECIFIC_TYPE>::type itor = elements->objects.find(key);
		if( itor != elements->objects.end())
		{
			elements->objects.erase(itor);
			return true;
		}
		return false;
	}

	/*
	*	清理SPECIFIC_TYPE类型容器
	*/
	template<class SPECIFIC_TYPE> void clear(){
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return;
		}
		elements->objects.clear();
	}

	/*
	*	访问SPECIFIC_TYPE类型容器
	*/
	template<class SPECIFIC_TYPE>
	void traverse(std::function<void(SPECIFIC_TYPE&)>  visitor)
	{
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return;
		}
		// 
		// 			typename iterator<SPECIFIC_TYPE>::type itor = elements->objects.begin();
		// 			while( itor != elements->objects.end())
		// 			{
		// 				visitor(itor->second);
		// 				++itor;
		// 			}

		int size = elements->objects.size();
		std::vector<SPECIFIC_TYPE> temp_objects;
		int pos = 0;
		temp_objects.resize(size);
		typename iterator<SPECIFIC_TYPE>::type itor = elements->objects.begin();
		while( itor != elements->objects.end())
		{
			temp_objects[pos] = itor->second;
			++pos;
			++itor;
		}

		for(int i=0; i<size; i++)
		{
			visitor(temp_objects[i]);
		}
	}

	/*
	*	访问SPECIFIC_TYPE类型容器（带KEY）
	*/
	template<class SPECIFIC_TYPE>
	void traverse_ex(std::function<void(const ContainerKey&, SPECIFIC_TYPE&)>  visitor)
	{
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return;
		}

		typename std::map<ContainerKey, SPECIFIC_TYPE> temp_objects;
		typename iterator<SPECIFIC_TYPE>::type itor = elements->objects.begin();
		while( itor != elements->objects.end())
		{
			temp_objects.insert(std::make_pair(itor->first, itor->second));
			++itor;
		}

		typename iterator<SPECIFIC_TYPE>::type temp_objects_itor = temp_objects.begin();
		while( temp_objects_itor != temp_objects.end())
		{
			visitor(temp_objects_itor->first, temp_objects_itor->second);
			++temp_objects_itor;
		}
	}

	CONTAINER & containers(void) { 
		return containers_; 
	}

	const CONTAINER & containers(void) const { 
		return containers_;
	}

private:
	/*
	*	找到SPECIFIC_TYPE类型的容器
	*/
	template<class SPECIFIC_TYPE, class T> 
	TypeContainers<ContainerKey, SPECIFIC_TYPE>* _Get(TypeContainers<ContainerKey, TypePair <SPECIFIC_TYPE, T> > &elements, SPECIFIC_TYPE* obj){
		return &elements.head_container;
	};

	/*
	*	未找到SPECIFIC_TYPE类型的容器，进一步查找
	*/
	template<class SPECIFIC_TYPE, class H, class T> 
	TypeContainers<ContainerKey, SPECIFIC_TYPE>* _Get(TypeContainers< ContainerKey, TypePair <H, T> >& elements, SPECIFIC_TYPE* obj){
		return _Get(elements.tail_container, obj);
	};

	/*
	*	未找到SPECIFIC_TYPE类型的容器，容器遍历完毕
	*/
	template<class SPECIFIC_TYPE> 
	TypeContainers<ContainerKey, SPECIFIC_TYPE>* _Get(TypeContainers<ContainerKey, TypeNull> &elements, SPECIFIC_TYPE* obj){
		return 0;
	};

	CONTAINER containers_;
};

NS_UTIL_BOOST_END
NS_DS_END

#endif