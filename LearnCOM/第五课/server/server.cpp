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
    int c = InterlockedDecrement(&m_Ref);
    if (c == 0) {
        delete this;
    }
    return c;
}

//+---------------------------------------------------------------------------
//
//  ����:  Display
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

