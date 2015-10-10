#ifndef __DIOS_UTIL_BOOST_MULTI_TYPE_CONTAINER___
#define __DIOS_UTIL_BOOST_MULTI_TYPE_CONTAINER___

#include <map>
#include <vector>


#include "dios_util_boost_lib.h"

/*
	Ŀ��:
		ʵ��������ͼ�ռ����������ͼʵ�����(��ͼʵ�������������������)������洢��ͼʵ���ģ�顣
		һ��������дһ����ͼʵ��Ļ��࣬Ȼ��������ͷ��벻ͬ�������С�������õ����ⶼ����ô�����ͨ��������
		��������д���Ĵ�����һ���Եģ�������ǰ����Ŀһ�������⡣
		����һ���취����ģ�忩��ʵ��һ�����ڵ�����������

	����: 
		ʵ��һ�������͵�������ʵ��ָ�����͵Ĳ��ң���ӣ�ɾ��������

	ʹ��:
		��һ��ģ�������ʾ�洢���������ͣ������������ȵ�ͼʵ�嶼��ʹ��UUID���й���ģ���ôʹ������
			CMultiTypeContainer<UUID, Player, Creature, OtherMapEntity ...>

	����:
		������������ӵ�ʱ��ֻ��Ҫ��ģ���������������ͼ��ɡ�

	��ע:
		������֧�����9������ͬʱ�洢��һ�������С�
	
	����:
	MiscHelper::CMultiTypeContainer<int, int, double, B> test_container;
	// ����ֵ
	test_container.insert<double>(0,11.0);
	test_container.insert<double>(0,10);
	test_container.insert<B>(0,B());
	// ��������ָ��
	std::shared_ptr<int> test_val_temp(new int(15));
	test_container.insert(1,test_val_temp);
	// ��ȡ����
	std::shared_ptr<int> test_val= test_container.find<int>(0);
	std::shared_ptr<double> test_val1 = test_container.find<double>(0);
	// ��ȡ��С
	std::cout<<test_container.size<int>()<<"-"<<test_container.size<double>()<<endl;
	// ����
	test_container.visit<int>(std::bind(Test, _1));
	// ɾ��
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
*	��Ԫ����
*/
template<class ContainerKey, class T> struct TypeContainers
{
	std::map<ContainerKey, T> objects;
};

template<class ContainerKey> struct TypeContainers<ContainerKey, TypeNull>
{
};

/*
*	��������
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
	*	��ȡSPECIFIC_TYPE����������С
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
	*	��ȡSPECIFIC_TYPE���Ͷ���
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
	*	����SPECIFIC_TYPE���Ͷ���
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
	*	�Ƴ�SPECIFIC_TYPE���Ͷ���
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
	*	����SPECIFIC_TYPE��������
	*/
	template<class SPECIFIC_TYPE> void clear(){
		TypeContainers<ContainerKey, SPECIFIC_TYPE>* elements = _Get(containers_, (SPECIFIC_TYPE*)0);
		if(!elements) {
			return;
		}
		elements->objects.clear();
	}

	/*
	*	����SPECIFIC_TYPE��������
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
	*	����SPECIFIC_TYPE������������KEY��
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
	*	�ҵ�SPECIFIC_TYPE���͵�����
	*/
	template<class SPECIFIC_TYPE, class T> 
	TypeContainers<ContainerKey, SPECIFIC_TYPE>* _Get(TypeContainers<ContainerKey, TypePair <SPECIFIC_TYPE, T> > &elements, SPECIFIC_TYPE* obj){
		return &elements.head_container;
	};

	/*
	*	δ�ҵ�SPECIFIC_TYPE���͵���������һ������
	*/
	template<class SPECIFIC_TYPE, class H, class T> 
	TypeContainers<ContainerKey, SPECIFIC_TYPE>* _Get(TypeContainers< ContainerKey, TypePair <H, T> >& elements, SPECIFIC_TYPE* obj){
		return _Get(elements.tail_container, obj);
	};

	/*
	*	δ�ҵ�SPECIFIC_TYPE���͵������������������
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