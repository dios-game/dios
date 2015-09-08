#ifndef __DIOS_PLATFORM_MACROS_H__
#define __DIOS_PLATFORM_MACROS_H__

/**
 * define some platform specific macros;
 */
#include "platform_config.h"

// generic macros
#define NS_DS_BEGIN namespace dios {
#define NS_DS_END }
#define USING_NS_DS using namespace dios

/*
 *	DS_PROPERTY + DS_PROPERTY_PASS_BY_REF + DS_REF_PROPERTY;
	基本变量;
 */
#define DS_PROPERTY(varType, varName)\
protected: varType varName##_;\
public: virtual varType varName(void) const { return varName##_; }\
public: virtual void set_##varName(varType varName) { varName##_ = varName; }

#define DS_PROPERTY_PASS_BY_REF(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }\
public: virtual void set_##varName(const varType& varName) { varName##_ = varName; }

#define DS_REF_PROPERTY(varType, varName)\
protected: varType varName##_;\
public: virtual varType& varName(void) { return varName##_; }\
public: virtual const varType& varName(void) const { return varName##_; }

#define DS_REF_PROPERTY2(varType, varName)\
protected: varType varName##_;\
public: virtual void set_##varName(const varType& varName) { varName##_ = varName; }\
public: virtual varType& varName(void) { return varName##_; }\
public: virtual const varType& varName(void) const { return varName##_; }

/*
 *	DS_PROPERTY_READONLY + DS_PROPERTY_READONLY_PASS_BY_REF + DS_REF_PROPERTY_READONLY
	只读变量;
 */
#define DS_PROPERTY_READONLY(varType, varName)\
protected: varType varName##_;\
public: virtual varType varName(void) const { return varName##_; }

#define DS_PROPERTY_READONLY_PASS_BY_REF(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }

#define DS_REF_PROPERTY_READONLY(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }

/*
 *	
 */
#define DS_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define DS_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define DS_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define DS_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define DS_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define DS_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define DS_BREAK_IF(cond)            if(cond) break

/*
 * only certain compilers support __attribute__((deprecated));
 * deprecated,弃用. 如果在源文件在任何地方地方使用deprecated attribute函数,编译器将会发出警告;
 */

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define DS_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define DS_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define DS_DEPRECATED_ATTRIBUTE
#endif 


/*
 *	sleep;
 */
#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)
#define DS_SLEEP(x) do { Sleep(x); } while (0)
#else
#define DS_SLEEP(x) do { if(x>=1000) sleep(x/1000); else usleep(x*1000); } while (0)
#endif // 


/*
 *	assert;
 */
#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32 || DS_TARGET_PLATFORM == DS_PLATFORM_MAC)
#include <assert.h>
#define DS_ASSERT(cond, description)    assert(cond && description)
#elif (DS_TARGET_PLATFORM == DS_PLATFORM_LINUX || DS_TARGET_PLATFORM == DS_PLATFORM_IOS || DS_TARGET_PLATFORM == DS_PLATFORM_BLACKBERRY)
#include <assert.h>
#define DS_ASSERT(cond, description)    assert(cond && description)
#elif (DS_TARGET_PLATFORM == DS_PLATFORM_ANDROID)
#define DS_ASSERT(cond, description) \
	if (! (cond)) \
	{ \
		char content[256]; \
		sprintf(content, "%s[%s function:%s line:%d]", description, __FILE__, __FUNCTION__, __LINE__);  \
	}
#else
#define DS_ASSERT(cond, description)
#endif // 

/*
 *	NULL;
 */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/*
 *	dll export;
 */
#if (DS_TARGET_PLATFORM == DS_PLATFORM_WIN32)
#define DS_DLL_EXPORT __declspec(dllexport)
#define DS_DLL_IMPORT __declspec(dllimport)
#elif (DS_TARGET_PLATFORM == DS_PLATFORM_LINUX)
#define DS_DLL_EXPORT __attribute__ ((visibility ("default")))
#define DS_DLL_IMPORT __attribute__ ((visibility ("default")))
#else
#define DS_DLL_EXPORT
#define DS_DLL_IMPORT
#endif

/*
 *	运算;
 */
#define DS_MIN(x,y) (((x) > (y)) ? (y) : (x))
#define DS_MAX(x,y) (((x) < (y)) ? (y) : (x))

#define DS_WORD_LO(val)  ((DS_uint8) ((DS_uint16)(val) & 0xFF))
#define DS_WORD_HI(val)  ((DS_uint8) ((DS_uint16)(val) >> 8))
#define DS_DWORD_LO(val)  ((DS_uint16) ((DS_uint32)(val) & 0xFFFF))
#define DS_DWORD_HI(val)  ((DS_uint16) ((DS_uint32)(val) >> 16))

#define DS_RND8(val) ((((val) + 7)/8) * 8) // 返回一个比X大的最接近的8的倍数; 1-8-->8; 9-16-->16; 
#define DS_UPCASE(c) (((c)>='a' && (c) <= 'z') ? ((c) - 0x20) : (c)) // 将一个字母转换为大写;
#define DS_LOWCASE(c) (((c)>='A' && (c) <= 'Z') ? ((c) + 0x20) : (c)) // 将一个字母转换为小写;
#define DS_DECCHK(c) ((c)>='0' && (c)<='9') // 判断字符是不是10进值的数字;
#define DS_HEXCHK(c) (((c) >= '0' && (c)<='9')||(c)>='A' && (c)<= 'F')||((c)>='a' && (c)<='f')) // 判断字符是不是16进值的数字;
#define DS_INC_SAT(val) (val = ((val)+1 > (val)) ? (val)+1 : (val)) // 防止溢出的一个方法;

/*
 *	字符串操作;
 */
#define DS_STRING_PTR(str) ((str)->empty() ? NULL : &*(str)->begin())

/**
 * 急型单件;
 *    DS_SINGLETON(ISingleton)
 */  
#define DS_SINGLETON(singleton) static singleton* GetInstancePtr(){ static singleton  m_nSelf; return &m_nSelf;}

/**
 * 延迟型实例化单件;
 *    DS_SINGLETON_LAZY(ISingleton)
 *    DS_SINGLETON_LAZY_IMPL(ISingleton, CSingleton)
 */  
#define DS_SINGLETON_LAZY(singleton) static singleton* GetInstancePtr();
#define DS_SINGLETON_LAZY_IMPL(singleton, impl_class) singleton* singleton::GetInstancePtr(){ static impl_class  m_nSelf; return &m_nSelf;}

//! 缓型单件 ======== 
#define DS_LAZY_SINGLETON_H(singleton)\
public:\
	static singleton* Init()			{ if(NULL == s_pInstance) s_pInstance = new singleton;return s_pInstance; }\
	static void		  Destroy()			{ if(s_pInstance) { delete s_pInstance; s_pInstance = NULL; } }\
	static singleton* GetInstancePtr()	{ return s_pInstance; }\
	static singleton* Shared()			{ return Init(); }\
private:\
	static singleton* s_pInstance;\

#define DS_LAZY_SINGLETON_CPP(singleton) singleton *singleton::s_pInstance = NULL;

#endif // __DIOS_PLATFORM_MACROS_H__
