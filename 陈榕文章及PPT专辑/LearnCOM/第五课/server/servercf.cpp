/*****************************************************************
 *----------------------------------------------------------------
 *CHelloFactory����೧,���ڴ���CHello�������.
 *----------------------------------------------------------------
 *DllGetClassObject��Dll����Ҫ�ĵ�������,ÿ�����Dll����ʵ�ִ˺���,
 *�˺����ɿͻ��������COM�����,���ڴ����೧,�������೧�Ľӿڵ�ָ��.
 *----------------------------------------------------------------
 *DllRegisterServer��ע�����ע�����,
 *DllUnregisterServer��ע�����ɾ�������ע����Ϣ.
 *----------------------------------------------------------------
 *DLLCanUnloadNow�ж��Ƿ��ж�Ը����
 *----------------------------------------------------------------
******************************************************************/

#include "server.h"
HMODULE g_hModule;
//+-----------------------------------------------------------------------
//
//  ����: DllMain 
//
//  ���ܣ�Dll����ں���
//
//  ����:  
//------------------------------------------------------------------------
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

//+---------------------------------------------------------------------------
//
//  ����:  DllRegisterServer
//
//  ���ܣ� ע���������
//            CLSID
//               |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}
//                       |__InprocServer32--value(server.dll)
//
//  ����: ��
//
//----------------------------------------------------------------------------
STDAPI DllRegisterServer()
{
    //��ȡ��̬���·�����ļ���
    OLECHAR wszBuf[MAX_PATH];
    if (GetModuleFileNameW(g_hModule, wszBuf, MAX_PATH) == 0) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    OLECHAR wszKey[64];
    wcscpy(wszKey, L"CLSID\\");
    //����IDת����ע����е��ַ���
    StringFromGUID2(CLSID_CHello, &wszKey[6], 40);
    wcscat(wszKey, L"\\InprocServer32");

    //����ע���Ľṹ,��ע�������д�������Ϣ.
    //CLSID
    // |__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}-CLSID_Hello
    //        |__InprocServer32

    HKEY hk;
    RegCreateKeyExW(HKEY_CLASSES_ROOT, wszKey, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, NULL);
    RegSetValueExW(hk, NULL, 0, REG_SZ, (BYTE*)wszBuf, 2*(wcslen(wszBuf)+1));
    RegCloseKey(hk) ;
    return NOERROR;
}

//+---------------------------------------------------------------------------
//  ����:  DllUnregisterServer
//
//  ���ܣ� ע���������
//            CLSID
//               X|__{3fbb0c4f-ced5-45aa-9ab0-91f1a7be6870}
//                      X|__InprocServer32--value(server.dll)
//
//  ����: ��
//----------------------------------------------------------------------------
STDAPI DllUnregisterServer()
{
    HKEY hkCLSID;
    //Ҫɾ��һ���Ӽ��������丸����ɾ��,��Windows NT��,ֻ�е�һ�������Ӽ�ʱ��
    //��ɾ��,����Windows 98����ͬ���Ӽ�һ��ɾ��.
    //��HKEY_CLASSES_ROOT--->CLSID��,�����ؼ����hkCLSID;
    LONG err = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"CLSID", 0,
                            KEY_ALL_ACCESS, &hkCLSID);
    if (err == ERROR_SUCCESS) {
        OLECHAR wszCLSID[40];
        HKEY hkClassID;
        StringFromGUID2(CLSID_CHello, wszCLSID, 40);
        
        //��CLSID_Hello����Ӧ�ļ�,��������Ӧ�ľ��hkClassID.
        err = RegOpenKeyExW(hkCLSID, wszCLSID, 0, KEY_ALL_ACCESS, &hkClassID);
        if (err == ERROR_SUCCESS) {
            //ɾ��hkClassID�����Ӽ�"InprocServer32".
            RegDeleteKeyW(hkClassID, L"InprocServer32");
            //��Ϊ��Windosw CE�в�����ɾ�����򿪵�ע����
            RegCloseKey(hkClassID);
        }
        //ɾ��hkCLSID�����Ӽ�,CLSID_Hello����Ӧ���ַ���
        RegDeleteKeyW(hkCLSID, wszCLSID);
        RegCloseKey(hkCLSID);
    }
    return HRESULT_FROM_WIN32(err);
}

//+---------------------------------------------------------------------------
//
//  ����:  DllGetClassObject
//
//  ���ܣ� ���DLL��������,CoCreateInstance������CoGetClassObject�������ô˺���,
//         �Դ����೧�������೧�ӿ�ָ��.�ڱ�ʾ���в����˾�̬����,�����û���ε�
//         ��DllGetClassObjectʱ�����˶���೧����.���������ʱ��Ϳռ���˷�.
//
//  ����: ��
//
//----------------------------------------------------------------------------
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ppv)
{
    static CHelloFactory cfHello;
    if (clsid == CLSID_CHello) {
        return cfHello.QueryInterface(iid, ppv);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

//+---------------------------------------------------------------------------
//
//  ����:  DLLCanUnloadNow
//
//  ���ܣ� ���DLL��������,windows����ϵͳ��ͻ�����ݴ˺����ķ���ֵ�ж����
//         �����Ƿ��ж��.�ڱ�ʾ����Ϊ�˼����,ֱ�ӷ���S_FALSE.
//
//  ����: ��
//
//----------------------------------------------------------------------------
STDAPI DllCanUnloadNow()
{
    return S_FALSE;
}

