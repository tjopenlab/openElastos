// Server.cpp : Defines the initialization routines for the DLL.
/*
 *CHelloClassFactory组件类厂,用于创建CHello组件对象.
 *----------------------------------------------------------------
 *DllGetClassObject是Dll最重要的导出函数,每个组件Dll必须实现此函数,
 *此函数由客户程序或者COM库调用,用于创建类厂,并返回类厂的接口的指针.
 *----------------------------------------------------------------
 *DLLCanUnloadNow判断是否可卸栽该组件
 *----------------------------------------------------------------
*/
#include <iostream.h>
#include <assert.h>
#include <unknwn.h>	
#include <objbase.h>	
#include "server.h"

//类厂的CLSID,此ID可由UUIDGEN.EXE或GUIDGen.exe工具产生.
const CLSID CLSID_HelloFactory =
    {0x3fbb0c4f, 0xced5, 0x45aa, {0x9a,0xb0,0x91,0xf1,0xa7,0xbe,0x68,0x70}};

//+----------------------------------------------------------------------------
//
//  功能：CHelloFactory类结构定义.CHelloFactory从IClassFactory公有派生,
//        是IClassFactory接口的具体实现.类厂是COM对象的生产基地,COM库通
//        过类厂的成员函数CreateInstance创建对象.对应于每个COM类,有一个
//        类厂专用于该COM类的对象的创建.类厂本身也是一个COM对象,它支持
//        特殊的接口--IClassFactory.
//
//-----------------------------------------------------------------------------
class CHelloFactory : public IClassFactory
{
public:
	HRESULT  STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject) ;
    ULONG    STDMETHODCALLTYPE AddRef( void);
    ULONG    STDMETHODCALLTYPE Release( void);
    HRESULT  STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    HRESULT  STDMETHODCALLTYPE LockServer(BOOL fLock);
};

//+---------------------------------------------------------------------------
//
//  函数:  QueryInterface
//
//  功能： CHelloFactory的接口查询函数.,针对不同的接口ID,对接口指针进行调整.
//
//  参数: idd为待查询的接口ID；ppv为输出参数，用于取回待查询的接口指针.
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::QueryInterface(const IID & iid,void ** ppv)
{
    if (iid == IID_IUnknown || iid == IID_IClassFactory ||
            iid == CLSID_HelloFactory) {
        *ppv=(IClassFactory *)this;
    }
    else {
        *ppv=NULL;
        return E_NOINTERFACE;   //查无此接口
    }
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  函数:  AddRef
//
//  功能： 把引用计数加1,但为了防止多线程客户同时引用同一对象的接口时,
//        同时访问该引用记数,造成引用记数值出错,采用InterlockedIncrement()函数.
//
//  参数: 无.
//
//----------------------------------------------------------------------------
ULONG CHelloFactory::AddRef()
{
    return 1;
}

//+---------------------------------------------------------------------------
//
//  函数:  Release
//
//  功能： 把引用计数减1,但为了防止多线程客户同时引用同一对象的接口时,
//        同时访问该引用记数,造成引用记数值出错,采用InterlockedDecrement()函数.
//
//  参数: 无.
//
//----------------------------------------------------------------------------
ULONG CHelloFactory::Release()
{
    return 1;
}

//+---------------------------------------------------------------------------
//
//  函数:  CreateInstance
//
//  功能： 先创建组件对象，然后根据接口IID查询该接口，并把接口指针的指针返回给ppv.
//
//  参数: pUnknownOuter用于组件被聚合的情形，idd指出接口ID，ppv勇于取回返回值。
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::CreateInstance(IUnknown *pUnk, REFIID riid, void **ppv)
{ 
    *ppv = NULL;

    if (pUnk != NULL)
        return CLASS_E_NOAGGREGATION;

    CHello * pHello = new CHello();
    if (pHello == NULL) {
        return E_OUTOFMEMORY;
    }

    HRESULT hr = pHello->QueryInterface(riid, ppv);
    if (FAILED(hr)) {
        delete pHello;
    }
    return hr;
}

//+---------------------------------------------------------------------------
//
//  函数:  LockServer
//
//  功能： 锁定组件，当参数bLock为TRUE时,把锁记数器值加1.
//         当参数bLock为FALSE时，把锁记数器值减1.
//		   在本示例中为了简单起见,直接返回E_FAIL.
//  参数: fLock用于指示锁记数器值的加减。
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::LockServer(BOOL fLock)
{
    return E_FAIL;
}

//+---------------------------------------------------------------------------
//
//  函数:  DllGetClassObject
//
//  功能： 组件DLL导出函数,CoCreateInstance函数或CoGetClassObject函数调用此函数,
//         以创建类厂并返回类厂接口指针.在本示例中采用了静态变量,以免用户多次调
//         用DllGetClassObject时创建了多个类厂对象.这样会造成时间和空间的浪费.
//		   
//  参数: 无
//
//----------------------------------------------------------------------------
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ppv)
{
    static CHelloFactory cHelloFactory;
    if (clsid == CLSID_HelloFactory) {
        return cHelloFactory.QueryInterface(iid, ppv);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

//+---------------------------------------------------------------------------
//
//  函数:  DLLCanUnloadNow
//
//  功能： 组件DLL导出函数,windows操作系统或客户程序据此函数的返回值判断组件程序是否可卸载.
//		   在本示例中为了简单起见,直接返回S_FALSE.
//
//  参数: 无
//
//----------------------------------------------------------------------------
STDAPI DllCanUnloadNow()
{
    return S_FALSE;
}

