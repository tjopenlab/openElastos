#include <stdio.h>
#include "hello.h"

HRESULT RegisterExe();
HRESULT UnRegisterExe();

int __cdecl main(int argc, char* argv[])
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
    IClassFactory *pClassFactory;
    hr = CoGetClassObject(CLSID_CHello, CLSCTX_INPROC_SERVER, NULL,
                    IID_IClassFactory, (void **)&pClassFactory);   
    if (FAILED(hr)) {
        printf("CoGetClassObject failed [0x%x].\n", hr);
        CoUninitialize();
        return hr;
    }
    //��COM���еǼ�pClassFactory 
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
    RegCloseKey(hk) ;
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

