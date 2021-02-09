#include <stdio.h>
#include "..\server\server.h"

int __cdecl main(int argc ,char * argv[])
{

    HINSTANCE  ghInstance=0;
    IClassFactory * pClassFactory;
    IHello * pHello;

    //Ϊ��ʹ��COM��,ʹ��COM�⺯��ǰ,�������CoInitialize()
    if (!SUCCEEDED(CoInitialize(NULL))){
        printf("Initialize COM library failed!\n");
        return -1;
    }

    //װ��DLL�ļ�,������ָ���DLLģ��ľ��
    ghInstance=::LoadLibraryW(L"..\\server\\server.dll");
    if (ghInstance==NULL) {
        printf("LoadLibrary Failed!\n");
        return -1;
    }

    //����ָ�����ĺ���ָ��
    typedef HRESULT (_stdcall * PDllGetClassObject)(const CLSID& clsid, 
                            const IID & idd,void ** ppv);
    //���ָ��DllGetClassObject()�������ĵ�ַָ��
    PDllGetClassObject pDllGetClassObject=(PDllGetClassObject)GetProcAddress(
                            ghInstance,"DllGetClassObject");
    if (pDllGetClassObject==NULL) {
        printf("GetProcAddress Failed!!\n");
        return -1;
    }
    //���á�
    (*pDllGetClassObject)(CLSID_CHello,IID_IClassFactory,
                            (void **)&pClassFactory);/*Get IClassFactoty*/

    //�����������ʵ��,�����ؽӿ�ָ��.
    HRESULT hr=pClassFactory->CreateInstance(NULL,IID_IHello,(void **)&pHello);
    if (FAILED(hr) || pHello== NULL) {
        printf("Create object failed!\n");
        return -1;
    }

    pHello->Display(("Hello World!"));
    pHello->Release();
    pClassFactory->Release();

    //ж��DLLģ��
    FreeLibrary(ghInstance);

    //ʹ������COM��,�������CoUnInitialize()
    CoUninitialize();
    return 0;
}
