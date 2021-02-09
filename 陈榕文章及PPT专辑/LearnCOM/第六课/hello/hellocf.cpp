#include "hello_c.h"
HMODULE g_hModule;

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

    CHello * pHello = new CHello;
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
