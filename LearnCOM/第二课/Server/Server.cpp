#include "Server.h"

//CHello的构造函数,初始化引用记数为零.
CHello::CHello()
{
    m_Ref = 0;
}
//+---------------------------------------------------------------------------
//
//  函数:  QueryInterface
//
//  功能： CHelloFactory的接口查询函数.,针对不同的接口ID,对接口指针进行调整.
//
//  参数: idd为待查询的接口ID；ppv为输出参数，用于取回待查询的接口指针.
//  由于16字节结构即 CLSID（类标识符 GUID）和 IID（接口标识符 GUID）有些大
//  因而不能按值传递，所以当递传GUID 时，需要使用 REFCLSID 和 REFIID 作为
//  参数的数据类型。您需要为每个对象类型创建一个 CLSID，为每个自定义接口
//  创建一个 IID。 
//
//----------------------------------------------------------------------------
HRESULT CHello::QueryInterface(REFIID riid,void **ppvObject)
{
    if (riid == IID_IUnknown || riid == IID_IHello) {
        *ppvObject=(IUnknown *)(IHello *)this;
        ((IUnknown *)(*ppvObject))->AddRef();
    }
    else {
        *ppvObject=NULL;
        return E_NOINTERFACE;
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
ULONG CHello::AddRef()
{
    return (ULONG)InterlockedIncrement(&m_Ref);
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

ULONG CHello::Release()
{
    ULONG c = InterlockedDecrement(&m_Ref);
    if (!c) {
         delete this;
    }
    return c;
}

//+---------------------------------------------------------------------------
//
//  函数:  Display
//
//  功能： 显示  Server prints text : str;
//
//  参数: 欲显示的字符串.
//
//----------------------------------------------------------------------------
BOOL CHello::Display(char * str)
{
	printf("Server prints text : %s\n",str);
    return 0;
}

