#include <stdio.h>
#include <unknwn.h>

const CLSID CLSID_CHello =
    {0xa714fb6a, 0x63c2, 0x4996, {0xb6,0xe6,0x88,0xdb,0xb7,0x8d,0x56,0xaa}};

const IID IID_IHello =
    {0xa714fb69, 0x63c2, 0x4996, {0xb6,0xe6,0x88,0xdb,0xb7,0x8d,0x56,0xaa}};
 

struct IHello: public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Hello(BSTR inStr, BSTR* outStr) = 0;
};

int __cdecl main(int argc ,char * argv[])
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        printf("CoInitialize() failed [0x%x]\n", hr);
        return hr;
    }

    IClassFactory * pClassFactory;
    hr = CoGetClassObject(CLSID_CHello, CLSCTX_INPROC_SERVER, NULL,
                        IID_IClassFactory, (void **)&pClassFactory);  
    if (FAILED(hr)) {
        printf("CoGetClassObject() failed [0x%x]\n", hr);
        CoUninitialize();
        return hr;
    }

    IHello* pHello;
    hr = pClassFactory->CreateInstance(NULL, IID_IHello, (void **)&pHello);
    if (FAILED(hr)) {
        printf("CoCreateInstance() failed [0x%x]\n", hr);
        return hr;
    }

    BSTR strIn, strOut;
    strIn = SysAllocString(L"Hello");

    pHello->Hello(strIn, &strOut);
    printf("%S\n", strOut);

    SysFreeString(strIn);
    SysFreeString(strOut);

    pHello->Release();
    pClassFactory->Release();

    CoUninitialize();
    return NOERROR;    
}
