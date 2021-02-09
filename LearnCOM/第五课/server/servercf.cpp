/*****************************************************************
 *----------------------------------------------------------------
 *CHelloFactory组件类厂,用于创建CHello组件对象.
 *----------------------------------------------------------------
 *DllGetClassObject是Dll最重要的导出函数,每个组件Dll必须实现此函数,
 *此函数由客户程序或者COM库调用,用于创建类厂,并返回类厂的接口的指针.
 *----------------------------------------------------------------
 *DllRegisterServer在注册表中注册组件,
 *DllUnregisterServer在注册表中删除组件的注册信息.
 *----------------------------------------------------------------
 *DLLCanUnloadNow判断是否可卸栽该组件
 *----------------------------------------------------------------
******************************************************************/

#include "server.h"
HMODULE g_hModule;
//+-----------------------------------------------------------------------
//
//  函数: DllMain 
//
//  功能：Dll的入口函数
//
//  参数:  
//------------------------------------------------------------------------
BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    g_hModule = (HMODULE) hModule;
    return TRUE;
}

class CHelloFactory : public IClassFactory
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* p, REFIID i, void** v);
    HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
};
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
HRESULT CHelloFactory::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IClassFactory) {
        *ppv = (IClassFactory *)this;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    return S_OK;
}

ULONG CHelloFactory::AddRef()
{
    return 1;
}

ULONG CHelloFactory::Release()
{
    return 1;
}

//+---------------------------------------------------------------------------
//
//  函数:  CreateInstance
//
//  功能：创建组件对象，然后根据接口IID查询该接口，并把接口指针的指针返回给ppv
//
//  参数: pUnknownOuter用于组件被聚合的情形,idd指出接口ID,ppv取回返回值。
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::CreateInstance(IUnknown* pUnk, REFIID riid, void** ppv)
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

HRESULT CHelloFactory::LockServer(BOOL fLock)
{
    return E_FAIL;
}

//+---------------------------------------------------------------------------
//
//  函数:  DllRegisterServer
//
//  功能： 注册组件对象
//            CLSID
//               |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}
//                       |__InprocServer32--value(server.dll)
//
//  参数: 无
//
//----------------------------------------------------------------------------
STDAPI DllRegisterServer()
{
    //获取动态库的路径及文件名
    OLECHAR wszBuf[MAX_PATH];
    if (GetModuleFileNameW(g_hModule, wszBuf, MAX_PATH) == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    OLECHAR wszKey[64];
    wcscpy(wszKey, L"CLSID\\");
    //把类ID转换成注册表中的字符串
    StringFromGUID2(CLSID_CHello, &wszKey[6], 40);
    wcscat(wszKey, L"\\InprocServer32");

    //根据注册表的结构,在注册表中填写本组件信息.
    //CLSID
    // |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}-CLSID_Hello
    //        |__InprocServer32

    HKEY hk;
    RegCreateKeyExW(HKEY_CLASSES_ROOT, wszKey, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, NULL);
    RegSetValueExW(hk, NULL, 0, REG_SZ, (BYTE*)wszBuf, 2*(wcslen(wszBuf)+1));
    RegCloseKey(hk) ;
    return NOERROR;
}

//+---------------------------------------------------------------------------
//  函数:  DllUnregisterServer
//
//  功能： 注消组件对象
//            CLSID
//               X|__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}
//                      X|__InprocServer32--value(server.dll)
//
//  参数: 无
//----------------------------------------------------------------------------
STDAPI DllUnregisterServer()
{
    HKEY hkCLSID;
    //要删除一个子键必须在其父键处删除,在Windows NT中,只有当一个键无子键时才
    //可删除,而在Windows 98可连同其子键一起删除.
    //打开HKEY_CLASSES_ROOT--->CLSID键,并返回键句柄hkCLSID;
    LONG err = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0,
                            KEY_ALL_ACCESS, &hkCLSID);
    if (err == ERROR_SUCCESS) {
        OLECHAR wszCLSID[40];
        HKEY hkClassID;
        StringFromGUID2(CLSID_CHello, wszCLSID, 40);
        
        //打开CLSID_Hello所对应的键,返回所对应的句柄hkClassID.
        err = RegOpenKeyExW(hkCLSID, wszCLSID, 0, KEY_ALL_ACCESS, &hkClassID);
        if (err == ERROR_SUCCESS) {
            //删除hkClassID键的子键"InprocServer32".
            RegDeleteKeyW(hkClassID, L"InprocServer32");
            //因为在Windosw CE中不允许删除被打开的注册表键
            RegCloseKey(hkClassID);
        }
        //删除hkCLSID键的子键,CLSID_Hello所对应的字符串
        RegDeleteKeyW(hkCLSID, wszCLSID);
        RegCloseKey(hkCLSID);
    }
    return HRESULT_FROM_WIN32(err);
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
    static CHelloFactory cfHello;
    if (clsid == CLSID_CHello) {
        return cfHello.QueryInterface(iid, ppv);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

//+---------------------------------------------------------------------------
//
//  函数:  DLLCanUnloadNow
//
//  功能： 组件DLL导出函数,windows操作系统或客户程序据此函数的返回值判断组件
//         程序是否可卸载.在本示例中为了简单起见,直接返回S_FALSE.
//
//  参数: 无
//
//----------------------------------------------------------------------------
STDAPI DllCanUnloadNow()
{
    return S_FALSE;
}

