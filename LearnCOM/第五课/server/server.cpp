#include "server.h"

//+---------------------------------------------------------------------------
//
//  函数:  QueryInterface
//
//  功能： CHello的接口查询函数
//
//  参数: idd为待查询的接口ID；
//        ppv为输出参数，用于取回待查询的接口指针
//
//  注释: 由于16字节结构即 CLSID和IID有些大,因而不能按值传递,所以当递传GUID时,
//        需要使用REFCLSID和REFIID作为参数的数据类型。
//
//---------------------------------------------------------------------------
HRESULT CHello::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IHello) {
        *ppv = (IHello *)this;
        this->AddRef();
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  函数:  AddRef
//
//  功能： 把引用计数加1,但为了防止多线程客户同时引用同一对象的接口时,同时访
//         问该引用记数,造成引用记数值出错,采用InterlockedIncrement()函数.
//
//  参数: 无.
//
//----------------------------------------------------------------------------
ULONG CHello::AddRef()
{
    return (ULONG)InterlockedIncrement(&m_Ref);
}

//+---------------------------------------------------------------------------
//
//  函数:  Release
//
//  功能： 把引用计数减1,但为了防止多线程客户同时引用同一对象的接口时,同时访
//         问该引用记数,造成引用记数值出错,采用InterlockedDecrement()函数.
//
//  参数:  无
//
//----------------------------------------------------------------------------
ULONG CHello::Release()
{
    int c = InterlockedDecrement(&m_Ref);
    if (c == 0) {
        delete this;
    }
    return c;
}

//+---------------------------------------------------------------------------
//
//  函数:  Display
//
//  功能： 显示 
//
//  参数: 欲显示的字符串.
//
//----------------------------------------------------------------------------
HRESULT CHello::Hello(BSTR inStr, BSTR* outStr)
{
    OLECHAR wszBuf[MAX_PATH];
    wcscpy(wszBuf, inStr);
    wcscat(wszBuf, L", World!");
    *outStr = SysAllocString(wszBuf);
    return NOERROR;
}

