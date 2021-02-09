#include <stdio.h>
#include "oaidl.h"

const CLSID CLSID_CHello =
    {0xa714fb6a, 0x63c2, 0x4996, {0xb6,0xe6,0x88,0xdb,0xb7,0x8d,0x56,0xaa}};

const IID IID_IHello =
    {0xa714fb69, 0x63c2, 0x4996, {0xb6,0xe6,0x88,0xdb,0xb7,0x8d,0x56,0xaa}};

struct IHello: public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Hello(BSTR inStr, BSTR* outStr) = 0;
};

class CHello: public IHello
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE Hello(BSTR inStr, BSTR* outStr);

    CHello()    : m_Ref(0) { }
    ~CHello()   { }
    LONG m_Ref;
};
