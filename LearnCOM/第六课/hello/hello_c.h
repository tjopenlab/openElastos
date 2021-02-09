#ifndef _HELLO_H_
#define _HELLO_H_

#include <stdio.h>
#include "hello.h"

class CHello: public IHello
{
private:
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE Hello(BSTR inStr, BSTR* outStr);

    CHello()    : m_Ref(0) { }
    LONG m_Ref;
};

#endif
