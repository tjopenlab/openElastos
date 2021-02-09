#include <stdio.h>
#include  <hello.h>

int __cdecl main(int argc ,char * argv[])
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        printf("CoInitialize() failed [0x%x]\n", hr);
        return hr; 
    }

    IHello* pHello = NULL;
    hr = CoCreateInstance(CLSID_CHello, NULL, CLSCTX_LOCAL_SERVER,
                                IID_IHello, (void **)&pHello);
    if (FAILED(hr)) {
        printf("CoGetClassObject() failed [0x%x]\n", hr);
        CoUninitialize();
        return hr;
    }

    BSTR strIn, strOut;
    strIn = SysAllocString(L"Hello");

    //调用对象接口函数
    pHello->Hello(strIn, &strOut);
    printf("%S\n", strOut);

    SysFreeString(strIn);
    SysFreeString(strOut);

    pHello->Release();
    CoUninitialize();
    return 0;    
}
