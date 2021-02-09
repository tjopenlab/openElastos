#include "stdio.h"
#include "server.h"

//+---------------------------------------------------------------------------
//
//  ����:  QueryInterface
//
//  ���ܣ� CHello�Ľӿڲ�ѯ����
//
//  ����: iddΪ����ѯ�Ľӿ�ID��
//        ppvΪ�������������ȡ�ش���ѯ�Ľӿ�ָ��
//
//  ע��: ����16�ֽڽṹ�� CLSID��IID��Щ��,������ܰ�ֵ����,���Ե��ݴ�GUIDʱ,
//        ��Ҫʹ��REFCLSID��REFIID��Ϊ�������������͡�
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
//  ����:  AddRef
//
//  ���ܣ� �����ü�����1,��Ϊ�˷�ֹ���߳̿ͻ�ͬʱ����ͬһ����Ľӿ�ʱ,ͬʱ��
//         �ʸ����ü���,������ü���ֵ����,����InterlockedIncrement()����.
//
//  ����: ��.
//
//----------------------------------------------------------------------------
ULONG CHello::AddRef()
{
    return (ULONG)InterlockedIncrement(&m_Ref);
}

//+---------------------------------------------------------------------------
//
//  ����:  Release
//
//  ���ܣ� �����ü�����1,��Ϊ�˷�ֹ���߳̿ͻ�ͬʱ����ͬһ����Ľӿ�ʱ,ͬʱ��
//         �ʸ����ü���,������ü���ֵ����,����InterlockedDecrement()����.
//
//  ����:  ��
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
//  ����: Hello 
//
//  ���ܣ� ��ʾ
//
//  ����: ����ʾ���ַ���.
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
//  ����:  QueryInterface
//
//  ���ܣ� CHello�Ľӿڲ�ѯ����
//
//  ����: iddΪ����ѯ�Ľӿ�ID��
//        ppvΪ�������������ȡ�ش���ѯ�Ľӿ�ָ��
//
//  ע��: ����16�ֽڽṹ�� CLSID��IID��Щ��,������ܰ�ֵ����,���Ե��ݴ�GUIDʱ,
//        ��Ҫʹ��REFCLSID��REFIID��Ϊ�������������͡�
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
//  ����:  CreateInstance
//
//  ���ܣ������������Ȼ����ݽӿ�IID��ѯ�ýӿڣ����ѽӿ�ָ���ָ�뷵�ظ�ppv
//
//  ����: pUnknownOuter����������ۺϵ�����,iddָ���ӿ�ID,ppvȡ�ط���ֵ��
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
    //ȡ�ص�ǰ���������·��,����ע����еǼ���
    OLECHAR wszBuf[MAX_PATH];
    if (GetModuleFileNameW(NULL, wszBuf, MAX_PATH) == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    OLECHAR wszKey[64];
    wcscpy(wszKey, L"CLSID\\");
    //����IDת����ע����е��ַ���
    StringFromGUID2(CLSID_CHello, &wszKey[6], 40);
    wcscat(wszKey, L"\\LocalServer32");

     //����CLSID_CHello���Ӽ�InprocServer32��
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
    //Ҫɾ��һ���Ӽ��������丸����ɾ��,��Windows NT��,
    //ֻ�е�һ�������Ӽ�ʱ�ſ�ɾ��,����Windows 98����ͬ���Ӽ�һ��ɾ��.
    //��HKEY_CLASSES_ROOT--->CLSID��,�����ؼ����hkCLSID
    LONG err = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0,
                            KEY_ALL_ACCESS, &hkCLSID);
    if (err == ERROR_SUCCESS) {
        OLECHAR wszCLSID[40];
        HKEY hkClassID;

        StringFromGUID2(CLSID_CHello, wszCLSID, 40);
        //��CLSID_CHello����Ӧ�ļ�,�����ؼ����hkClassID
        err = RegOpenKeyExW(hkCLSID, wszCLSID, 0, KEY_ALL_ACCESS, &hkClassID);
        if (err == ERROR_SUCCESS) {
            //ɾ��hkClassID�����Ӽ�"InprocServer32"
            RegDeleteKeyW(hkClassID, L"LocalServer32");
            RegCloseKey(hkClassID);
        }
        //ɾ��CLSID�����Ӽ�,CLSID_CHello����Ӧ���ַ���
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
    //�����೧����
    CHelloFactory * pClassFactory = new CHelloFactory;
    //��COM���еǼ�ClassFactory
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
    //��������Ϣѭ��,ֱ���յ�WM_QUIT��Ϣ�����˳�ѭ��
    while (GetMessage(&msg,NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //����೧��������COM�������У������ɾ�����೧����
    CoRevokeClassObject(dwRegister);
    CoUninitialize();
    return 0;
}

