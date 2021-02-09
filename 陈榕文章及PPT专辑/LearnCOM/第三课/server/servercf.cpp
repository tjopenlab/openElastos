#include "server.h"

HMODULE g_hModule;
//添加Dll入口函数的目的是为了保存入口函数的参数hModule,
//g_hModule为在组件的注册函数DllRegisterServer中的:GetModuleFileName的参数,
//用以获取组件Dll的完整路径,并在注册表中注册该组件.
//如果不是为了此目的,本例子中可不用该入口函数
BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
    g_hModule = (HMODULE)hModule;
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
//  CLSID
//   |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}--value("This is a test for com")
//      |__InprocServer32--value(E:\\temp\\COMTest\\Server\\Debug\\server.dll)
//
//  参数: 无
//
//----------------------------------------------------------------------------
STDAPI DllRegisterServer()
{
    OLECHAR wszBuf[MAX_PATH];
    if (GetModuleFileNameW(g_hModule, wszBuf, MAX_PATH) == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    OLECHAR wszKey[64];
    wcscpy(wszKey, L"CLSID\\");
    StringFromGUID2(CLSID_CHello, &wszKey[6], 40);
    wcscat(wszKey, L"\\InprocServer32");

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
//  CLSID
//   |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}--value("This is a test for com")
//      |__InprocServer32--value(E:\\temp\\COMTest\\Server\\Debug\\server.dll)
//
//  参数: 无
//----------------------------------------------------------------------------
STDAPI DllUnregisterServer()
{
    HKEY hkCLSID;
    LONG err = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0,
                            KEY_ALL_ACCESS, &hkCLSID);
    if (err == ERROR_SUCCESS) {
        OLECHAR wszCLSID[40];
        HKEY hkClassID;

        StringFromGUID2(CLSID_CHello, wszCLSID, 40);
        err = RegOpenKeyExW(hkCLSID, wszCLSID, 0, KEY_ALL_ACCESS, &hkClassID);
        if (err == ERROR_SUCCESS) {
            RegDeleteKeyW(hkClassID, L"InprocServer32");
            RegCloseKey(hkClassID);
        }
        RegDeleteKeyW(hkCLSID, wszCLSID);
        RegCloseKey(hkCLSID);
    }
    return HRESULT_FROM_WIN32(err);
}

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ppv)
{
    static CHelloFactory cfHello;
    if (clsid == CLSID_CHello) {
        return cfHello.QueryInterface(iid, ppv);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
    return S_FALSE;
}

