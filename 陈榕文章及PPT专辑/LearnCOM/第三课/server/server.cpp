#include "server.h"

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

ULONG CHello::AddRef()
{
    return (ULONG)InterlockedIncrement(&m_Ref);
}

ULONG CHello::Release()
{
    ULONG c = InterlockedDecrement(&m_Ref);
    if (c == 0) {
        delete this;
    }
    return c;
}

HRESULT CHello::Hello(BSTR inStr, BSTR* outStr)
{
    OLECHAR wszBuf[MAX_PATH];
    wcscpy(wszBuf, inStr);
    wcscat(wszBuf, L", World!");
    *outStr = SysAllocString(wszBuf);
    return NOERROR;
}

