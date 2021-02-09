// Server.cpp : Defines the initialization routines for the DLL.
/*
 *CHelloClassFactory����೧,���ڴ���CHello�������.
 *----------------------------------------------------------------
 *DllGetClassObject��Dll����Ҫ�ĵ�������,ÿ�����Dll����ʵ�ִ˺���,
 *�˺����ɿͻ��������COM�����,���ڴ����೧,�������೧�Ľӿڵ�ָ��.
 *----------------------------------------------------------------
 *DLLCanUnloadNow�ж��Ƿ��ж�Ը����
 *----------------------------------------------------------------
*/
#include <iostream.h>
#include <assert.h>
#include <unknwn.h>	
#include <objbase.h>	
#include "server.h"

//�೧��CLSID,��ID����UUIDGEN.EXE��GUIDGen.exe���߲���.
const CLSID CLSID_HelloFactory =
    {0x3fbb0c4f, 0xced5, 0x45aa, {0x9a,0xb0,0x91,0xf1,0xa7,0xbe,0x68,0x70}};

//+----------------------------------------------------------------------------
//
//  ���ܣ�CHelloFactory��ṹ����.CHelloFactory��IClassFactory��������,
//        ��IClassFactory�ӿڵľ���ʵ��.�೧��COM�������������,COM��ͨ
//        ���೧�ĳ�Ա����CreateInstance��������.��Ӧ��ÿ��COM��,��һ��
//        �೧ר���ڸ�COM��Ķ���Ĵ���.�೧����Ҳ��һ��COM����,��֧��
//        ����Ľӿ�--IClassFactory.
//
//-----------------------------------------------------------------------------
class CHelloFactory : public IClassFactory
{
public:
	HRESULT  STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject) ;
    ULONG    STDMETHODCALLTYPE AddRef( void);
    ULONG    STDMETHODCALLTYPE Release( void);
    HRESULT  STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    HRESULT  STDMETHODCALLTYPE LockServer(BOOL fLock);
};

//+---------------------------------------------------------------------------
//
//  ����:  QueryInterface
//
//  ���ܣ� CHelloFactory�Ľӿڲ�ѯ����.,��Բ�ͬ�Ľӿ�ID,�Խӿ�ָ����е���.
//
//  ����: iddΪ����ѯ�Ľӿ�ID��ppvΪ�������������ȡ�ش���ѯ�Ľӿ�ָ��.
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::QueryInterface(const IID & iid,void ** ppv)
{
    if (iid == IID_IUnknown || iid == IID_IClassFactory ||
            iid == CLSID_HelloFactory) {
        *ppv=(IClassFactory *)this;
    }
    else {
        *ppv=NULL;
        return E_NOINTERFACE;   //���޴˽ӿ�
    }
    return S_OK;
}

//+---------------------------------------------------------------------------
//
//  ����:  AddRef
//
//  ���ܣ� �����ü�����1,��Ϊ�˷�ֹ���߳̿ͻ�ͬʱ����ͬһ����Ľӿ�ʱ,
//        ͬʱ���ʸ����ü���,������ü���ֵ����,����InterlockedIncrement()����.
//
//  ����: ��.
//
//----------------------------------------------------------------------------
ULONG CHelloFactory::AddRef()
{
    return 1;
}

//+---------------------------------------------------------------------------
//
//  ����:  Release
//
//  ���ܣ� �����ü�����1,��Ϊ�˷�ֹ���߳̿ͻ�ͬʱ����ͬһ����Ľӿ�ʱ,
//        ͬʱ���ʸ����ü���,������ü���ֵ����,����InterlockedDecrement()����.
//
//  ����: ��.
//
//----------------------------------------------------------------------------
ULONG CHelloFactory::Release()
{
    return 1;
}

//+---------------------------------------------------------------------------
//
//  ����:  CreateInstance
//
//  ���ܣ� �ȴ����������Ȼ����ݽӿ�IID��ѯ�ýӿڣ����ѽӿ�ָ���ָ�뷵�ظ�ppv.
//
//  ����: pUnknownOuter����������ۺϵ����Σ�iddָ���ӿ�ID��ppv����ȡ�ط���ֵ��
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::CreateInstance(IUnknown *pUnk, REFIID riid, void **ppv)
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

//+---------------------------------------------------------------------------
//
//  ����:  LockServer
//
//  ���ܣ� ���������������bLockΪTRUEʱ,����������ֵ��1.
//         ������bLockΪFALSEʱ������������ֵ��1.
//		   �ڱ�ʾ����Ϊ�˼����,ֱ�ӷ���E_FAIL.
//  ����: fLock����ָʾ��������ֵ�ļӼ���
//
//----------------------------------------------------------------------------
HRESULT CHelloFactory::LockServer(BOOL fLock)
{
    return E_FAIL;
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
    static CHelloFactory cHelloFactory;
    if (clsid == CLSID_HelloFactory) {
        return cHelloFactory.QueryInterface(iid, ppv);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

//+---------------------------------------------------------------------------
//
//  ����:  DLLCanUnloadNow
//
//  ���ܣ� ���DLL��������,windows����ϵͳ��ͻ�����ݴ˺����ķ���ֵ�ж���������Ƿ��ж��.
//		   �ڱ�ʾ����Ϊ�˼����,ֱ�ӷ���S_FALSE.
//
//  ����: ��
//
//----------------------------------------------------------------------------
STDAPI DllCanUnloadNow()
{
    return S_FALSE;
}

