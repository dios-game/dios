#ifndef __DIOS_COM_CONTEXT_H__
#define __DIOS_COM_CONTEXT_H__

#include "dios_com_lib.h"
#include "dios_com_interface.hpp"
#include "dios_com_factory.hpp"

NS_DS_BEGIN

/*
 *	ʵ�ֹ��ܣ����ز��;��ӹ���;�������;
 */

class CDynamicLib;
class CDynamicPlugins;
class CComFactories;

namespace detail{
	class DIOS_COM_DECL CComContext{

	public:
		CComContext();
		~CComContext();

		void SetLog(const std::function<void(int, const std::string&)>& log_callback);

		void LoadPlugin(const std::string& plugin_name);

		// ��̬����;
		void AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory);
		// ��̬����(���涯̬������ָ�뱣֤��̬�����);
		void AddFactory(const ComID& com_id, const detail::CComFactory::Ptr& factory, std::shared_ptr<CDynamicLib>& dynamic_lib_ptr);

		DS_SINGLETON(CComContext);

	private:
		ICom::Ptr _CreateCom(const ComID& com_id);

	private:
		CComFactories* factories_;
		CDynamicPlugins* plugins_;

		// helper	
	public:
		template <class T>
		void AddFactory(){
			ComID id = typeid(T).name();
			AddFactory(id, detail::CComFactory::CreateFactory<T>());
		}
		template <class T>
		void AddFactory(const ComID& com_id){
			AddFactory(com_id, detail::CComFactory::CreateFactory<T>());
		}
		template <class T>
		void AddFactory(std::shared_ptr<CDynamicLib>& dynamic_lib_ptr){
			ComID id = typeid(T).name();
			AddFactory(id, detail::CComFactory::CreateFactory<T>(), dynamic_lib_ptr);
		}
		template <class T>
		void AddFactory(const ComID& com_id, std::shared_ptr<CDynamicLib>& dynamic_lib_ptr){
			AddFactory(com_id, detail::CComFactory::CreateFactory<T>(), dynamic_lib_ptr);
		}

		template<class InterfaceType>
		inline std::shared_ptr<InterfaceType> CreateCom()
		{
			ComID com_id = typeid(InterfaceType).name();
			ICom::Ptr ptr = _CreateCom(com_id);
			if (ptr)
				return ptr->QueryInterface<InterfaceType>();
			return std::shared_ptr<InterfaceType>();
		}

		template<class InterfaceType>
		inline std::shared_ptr<InterfaceType> CreateCom(const ComID& com_id)
		{
			ICom::Ptr ptr = _CreateCom(com_id);
			if (ptr)
				return ptr->QueryInterface<InterfaceType>();
			return std::shared_ptr<InterfaceType>();
		}
	};
}

NS_DS_END

#define sComContext dios::detail::CComContext::GetInstancePtr()

#endif // __DIOS_COM_CONTEXT_H__
