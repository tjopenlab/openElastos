#include "stdio.h"
#include "server.h"

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

//+---------------------------------------------------------------------------
//
//  函数:  AddRef
//
//  功能： 把引用计数加1,但为了防止多线程客户同时引用同一对象的接口时,同时访
//         问该引用记数,造成引用记数值出错,采用InterlockedIncrement()函数.
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
//  功能： 把引用计数减1,但为了防止多线程客户同时引用同一对象的接口时,同时访
//         问该引用记数,造成引用记数值出错,采用InterlockedDecrement()函数.
//
//  参数:  无
//
//----------------------------------------------------------------------------
ULONG CHello::Release()
{
    ULONG c = InterlockedDecrement(&m_Ref);
    if (c == 0) {
        delete this;
    }
    return c;
}

//+---------------------------------------------------------------------------
//
//  函数: Hello 
//
//  功能： 显示
//
//  参数: 欲显示的字符串.
//
//----------------------------------------------------------------------------
HRESULT CHello::Hello(BSTR inStr, BSTR* outStr)
{
    OLECHAR wszBuf[MAX_PATH];
    wcscpy(wszBuf, inStr);
    wcscat(wszBuf, L", World!");
    *outStr = SysAllocString(wszBuf);
    return NOERROR;
}

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

HRESULT RegisterExe()
{
    //取回当前组件的完整路径,并在注册表中登记它
    OLECHAR wszBuf[MAX_PATH];
    if (GetModuleFileNameW(NULL, wszBuf, MAX_PATH) == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    OLECHAR wszKey[64];
    wcscpy(wszKey, L"CLSID\\");
    //把类ID转换成注册表中的字符串
    StringFromGUID2(CLSID_CHello, &wszKey[6], 40);
    wcscat(wszKey, L"\\LocalServer32");

     //创建CLSID_CHello和子键InprocServer32键
    HKEY hk;
    RegCreateKeyExW(HKEY_CLASSES_ROOT, wszKey, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, NULL);
    RegSetValueExW(hk, NULL, 0, REG_SZ, (BYTE*)wszBuf, 2*(wcslen(wszBuf)+1));
    RegCloseKey(hk);
    return NOERROR;
}

HRESULT UnRegisterExe()
{
    HKEY hkCLSID;
    //要删除一个子键必须在其父键处删除,在Windows NT中,
    //只有当一个键无子键时才可删除,而在Windows 98可连同其子键一起删除.
    //打开HKEY_CLASSES_ROOT--->CLSID键,并返回键句柄hkCLSID
    LONG err = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0,
                            KEY_ALL_ACCESS, &hkCLSID);
    if (err == ERROR_SUCCESS) {
        OLECHAR wszCLSID[40];
        HKEY hkClassID;

        StringFromGUID2(CLSID_CHello, wszCLSID, 40);
        //打开CLSID_CHello所对应的键,并返回键句柄hkClassID
        err = RegOpenKeyExW(hkCLSID, wszCLSID, 0, KEY_ALL_ACCESS, &hkClassID);
        if (err == ERROR_SUCCESS) {
            //删除hkClassID键的子键"InprocServer32"
            RegDeleteKeyW(hkClassID, L"LocalServer32");
            RegCloseKey(hkClassID);
        }
        //删除CLSID键的子键,CLSID_CHello所对应的字符串
        RegDeleteKeyW(hkCLSID, wszCLSID);
        RegCloseKey(hkCLSID);
    }
    return HRESULT_FROM_WIN32(err);
}

HRESULT __cdecl main(int argc, char* argv[])
{
    HRESULT hr;
    if ((argc > 1) &&
        _stricmp(argv[1], "-Embedding") != 0 &&
        _stricmp(argv[1], "/Embedding") != 0) {

        if (_stricmp(argv[1], "/REGSERVER") == 0) {
            hr = RegisterExe();
            if (FAILED(hr))
                printf("Failed to register %s [0x%x].\n", argv[0], hr);
        }
        else if (_stricmp(argv[1], "/UNREGSERVER") == 0) {
            hr = UnRegisterExe();
            if (FAILED(hr))
                printf("Failed to unregister %s [0x%x].\n", argv[0], hr);
        }
        else {
            printf("usage: %s /REGSERVER\n", argv[0]);
            printf("       %s /UNREGSERVER\n", argv[0]);
            printf("       %s /Embedding or -Embedding\n", argv[0]);
            hr = E_FAIL;
        }
        return hr;
    }

    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        printf("CoInitialize failed [0x%x].\n", hr);
        return hr;
    }
    //创建类厂对象
    CHelloFactory * pClassFactory = new CHelloFactory;
    //在COM库中登记ClassFactory
    DWORD dwRegister = 0;
    hr = CoRegisterClassObject(CLSID_CHello, (IUnknown *)pClassFactory,
                    CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
    if (FAILED(hr)) {
        printf("CoRegisterClassObject failed [0x%x].\n", hr);
        CoUninitialize();
        return hr;
    }

    printf("Waiting for client to connect...\n");
    MSG msg;
    //进行主消息循环,直到收到WM_QUIT消息，才退出循环
    while (GetMessage(&msg,NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //如果类厂对象仍在COM库的类表中，则从中删除该类厂对象
    CoRevokeClassObject(dwRegister);
    CoUninitialize();
    return 0;
}

