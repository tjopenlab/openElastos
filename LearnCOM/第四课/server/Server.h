#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include "hello.h"
class CHello:public IHello 
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE Hello(BSTR inStr, BSTR* outStr);
    CHello()    : m_Ref(0) { }
    ~CHello()   { PostQuitMessage(0); }
     LONG m_Ref;
};
/*-------------------------------------------------------------------------*/

class CHelloFactory : public IClassFactory
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* p, REFIID i, void** v);
    HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
};

#endif
