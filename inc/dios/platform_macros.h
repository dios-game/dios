#ifndef __DIOS_PLATFORM_MACROS_H__
#define __DIOS_PLATFORM_MACROS_H__

/**
 * define some platform specific macros;
 */
#include "platform_config.h"

// generic macros
#define NS_DIOS_BEGIN namespace dxm {
#define NS_DIOS_END }
#define USING_NS_DXM using namespace dxm

/*
 *	DIOS_PROPERTY + DIOS_PROPERTY_PASS_BY_REF + DIOS_REF_PROPERTY;
	��������;
 */
#define DIOS_PROPERTY(varType, varName)\
protected: varType varName##_;\
public: virtual varType varName(void) const { return varName##_; }\
public: virtual void set_##varName(varType varName) { varName##_ = varName; }

#define DIOS_PROPERTY_PASS_BY_REF(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }\
public: virtual void set_##varName(const varType& varName) { varName##_ = varName; }

#define DIOS_REF_PROPERTY(varType, varName)\
protected: varType varName##_;\
public: virtual varType& varName(void) { return varName##_; }\
public: virtual const varType& varName(void) const { return varName##_; }

#define DIOS_REF_PROPERTY2(varType, varName)\
protected: varType varName##_;\
public: virtual void set_##varName(const varType& varName) { varName##_ = varName; }\
public: virtual varType& varName(void) { return varName##_; }\
public: virtual const varType& varName(void) const { return varName##_; }

/*
 *	DIOS_PROPERTY_READONLY + DIOS_PROPERTY_READONLY_PASS_BY_REF + DIOS_REF_PROPERTY_READONLY
	ֻ������;
 */
#define DIOS_PROPERTY_READONLY(varType, varName)\
protected: varType varName##_;\
public: virtual varType varName(void) const { return varName##_; }

#define DIOS_PROPERTY_READONLY_PASS_BY_REF(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }

#define DIOS_REF_PROPERTY_READONLY(varType, varName)\
protected: varType varName##_;\
public: virtual const varType& varName(void) const { return varName##_; }

/*
 *	
 */
#define DIOS_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define DIOS_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define DIOS_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define DIOS_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define DIOS_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define DIOS_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define DIOS_BREAK_IF(cond)            if(cond) break

/*
 * only certain compilers support __attribute__((deprecated));
 * deprecated,����. �����Դ�ļ����κεط��ط�ʹ��deprecated attribute����,���������ᷢ������;
 */

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define DIOS_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define DIOS_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define DIOS_DEPRECATED_ATTRIBUTE
#endif 


/*
 *	sleep;
 */
#if (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_WIN32)
#define DIOS_SLEEP(x) do { Sleep(x); } while (0)
#else
#define DIOS_SLEEP(x) do { if(x>=1000) sleep(x/1000); else usleep(x*1000); } while (0)
#endif // 


/*
 *	assert;
 */
#if (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_WIN32 || DIOS_TARGET_PLATFORM == DIOS_PLATFORM_MAC)
#include <assert.h>
#define DIOS_ASSERT(cond, description)    assert(cond && description)
#elif (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_LINUX || DIOS_TARGET_PLATFORM == DIOS_PLATFORM_IOS || DIOS_TARGET_PLATFORM == DIOS_PLATFORM_BLACKBERRY)
#include <assert.h>
#define DIOS_ASSERT(cond, description)    assert(cond && description)
#elif (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_ANDROID)
#define DIOS_ASSERT(cond, description) \
	if (! (cond)) \
	{ \
		char content[256]; \
		sprintf(content, "%s[%s function:%s line:%d]", description, __FILE__, __FUNCTION__, __LINE__);  \
	}
#else
#define DIOS_ASSERT(cond, description)
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
#if (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_WIN32)
#define DIOS_DLL_EXPORT __declspec(dllexport)
#define DIOS_DLL_IMPORT __declspec(dllimport)
#elif (DIOS_TARGET_PLATFORM == DIOS_PLATFORM_LINUX)
#define DIOS_DLL_EXPORT __attribute__ ((visibility ("default")))
#define DIOS_DLL_IMPORT __attribute__ ((visibility ("default")))
#else
#define DIOS_DLL_EXPORT
#define DIOS_DLL_IMPORT
#endif

/*
 *	����;
 */
#define DIOS_MIN(x,y) (((x) > (y)) ? (y) : (x))
#define DIOS_MAX(x,y) (((x) < (y)) ? (y) : (x))

#define DIOS_WORD_LO(val)  ((DIOS_uint8) ((DIOS_uint16)(val) & 0xFF))
#define DIOS_WORD_HI(val)  ((DIOS_uint8) ((DIOS_uint16)(val) >> 8))
#define DIOS_DWORD_LO(val)  ((DIOS_uint16) ((DIOS_uint32)(val) & 0xFFFF))
#define DIOS_DWORD_HI(val)  ((DIOS_uint16) ((DIOS_uint32)(val) >> 16))

#define DIOS_RND8(val) ((((val) + 7)/8) * 8) // ����һ����X�����ӽ���8�ı���; 1-8-->8; 9-16-->16; 
#define DIOS_UPCASE(c) (((c)>='a' && (c) <= 'z') ? ((c) - 0x20) : (c)) // ��һ����ĸת��Ϊ��д;
#define DIOS_LOWCASE(c) (((c)>='A' && (c) <= 'Z') ? ((c) + 0x20) : (c)) // ��һ����ĸת��ΪСд;
#define DIOS_DECCHK(c) ((c)>='0' && (c)<='9') // �ж��ַ��ǲ���10��ֵ������;
#define DIOS_HEXCHK(c) (((c) >= '0' && (c)<='9')||(c)>='A' && (c)<= 'F')||((c)>='a' && (c)<='f')) // �ж��ַ��ǲ���16��ֵ������;
#define DIOS_INC_SAT(val) (val = ((val)+1 > (val)) ? (val)+1 : (val)) // ��ֹ�����һ������;

/*
 *	�ַ�������;
 */
#define DIOS_STRING_PTR(str) ((str)->empty() ? NULL : &*(str)->begin())

/**
 * ���͵���;
 *    DIOS_SINGLETON(ISingleton)
 */  
#define DIOS_SINGLETON(singleton) static singleton* GetInstancePtr(){ static singleton  m_nSelf; return &m_nSelf;}

/**
 * �ӳ���ʵ��������;
 *    DIOS_SINGLETON_LAZY(ISingleton)
 *    DIOS_SINGLETON_LAZY_IMPL(ISingleton, CSingleton)
 */  
#define DIOS_SINGLETON_LAZY(singleton) static singleton* GetInstancePtr();
#define DIOS_SINGLETON_LAZY_IMPL(singleton, impl_class) singleton* singleton::GetInstancePtr(){ static impl_class  m_nSelf; return &m_nSelf;}

//! ���͵��� ======== 
#define DIOS_LAZY_SINGLETON_H(singleton)\
public:\
	static singleton* Init()			{ if(NULL == s_pInstance) s_pInstance = new singleton;return s_pInstance; }\
	static void		  Destroy()			{ if(s_pInstance) { delete s_pInstance; s_pInstance = NULL; } }\
	static singleton* GetInstancePtr()	{ return s_pInstance; }\
	static singleton* Shared()			{ return Init(); }\
private:\
	static singleton* s_pInstance;\

#define DIOS_LAZY_SINGLETON_CPP(singleton) singleton *singleton::s_pInstance = NULL;

#endif // __DIOS_PLATFORM_MACROS_H__
