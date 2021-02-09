#include <stdio.h>
#include "..\server\server.h"

int __cdecl main(int argc ,char * argv[])
{

    HINSTANCE  ghInstance=0;
    IClassFactory * pClassFactory;
    IHello * pHello;

    //为了使用COM库,使用COM库函数前,必须调用CoInitialize()
    if (!SUCCEEDED(CoInitialize(NULL))){
        printf("Initialize COM library failed!\n");
        return -1;
    }

    //装载DLL文件,并返回指向该DLL模块的句柄
    ghInstance=::LoadLibraryW(L"..\\server\\server.dll");
    if (ghInstance==NULL) {
        printf("LoadLibrary Failed!\n");
        return -1;
    }

    //定义指向函数的函数指针
    typedef HRESULT (_stdcall * PDllGetClassObject)(const CLSID& clsid, 
                            const IID & idd,void ** ppv);
    //获得指向“DllGetClassObject()”函数的地址指针
    PDllGetClassObject pDllGetClassObject=(PDllGetClassObject)GetProcAddress(
                            ghInstance,"DllGetClassObject");
    if (pDllGetClassObject==NULL) {
        printf("GetProcAddress Failed!!\n");
        return -1;
    }
    //调用　
    (*pDllGetClassObject)(CLSID_CHello,IID_IClassFactory,
                            (void **)&pClassFactory);/*Get IClassFactoty*/

    //创建组件对象实例,并返回接口指针.
    HRESULT hr=pClassFactory->CreateInstance(NULL,IID_IHello,(void **)&pHello);
    if (FAILED(hr) || pHello== NULL) {
        printf("Create object failed!\n");
        return -1;
    }

    pHello->Display(("Hello World!"));
    pHello->Release();
    pClassFactory->Release();

    //卸载DLL模块
    FreeLibrary(ghInstance);

    //使用完了COM库,必须调用CoUnInitialize()
    CoUninitialize();
    return 0;
}
