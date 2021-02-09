#include <stdio.h>
#include <unknwn.h>	
#ifndef _SERVER_H_
#define _SERVER_H_	

//IHello�ӿڵ�ID,��ID����UUIDGEN.EXE��GUIDGen.exe���߲���.
const IID IID_IHello = 
    {0xe385b4d6, 0xc6b2,0x4cbb,{0xa3,0x43,0x04,0x3e,0xff,0x26,0x2c,0xa1}};

//CHello��� clsid,��clsid����UUIDGEN.EXE��GUIDGen.exe���߲���.
const CLSID CLSID_CHello=
    {0x3fbb0c4f, 0xced5, 0x45aa, {0x9a,0xb0,0x91,0xf1,0xa7,0xbe,0x68,0x70}};

//
//  ���ܣ� IHello�ӿڶ���.
//         ��ΪIUnknown�ӿ��Ѿ���unknwn.h�ļ���ʵ��,�ʲ����ٶ���IUnknown�ӿ�
//         �κ�COM�ӿڶ�Ӧ��ֱ�ӻ��ݴ�IUnknown����.�ӿڶ���ֻ����COM�Ľӿ�
//         �ṹ,��û�о����ʵ��, ����C++��vtable�ṹ��COM�ӿڽṹ��ȫ��һ��,
//         ��˲���C++����COM�ӿڽ�Ϊ���. C���ԵĽӿ�
//	       ���巽���ɲμ�<<COMԭ����Ӧ��>>�еĵ�27ҳ.
//
class IHello: public IUnknown //define  IHello interface's structure 
{
	public:
		virtual BOOL  Display(char * str)=0;//����Ϊ���麯��
};

//
//  ���ܣ� CHello��ṹ����.
//        CHello��IHello��������,��IHello�ӿڵľ���ʵ��.
//
class CHello:public IHello //Implement IHello interface's structure 
{
	public:
		CHello();
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void **ppvObject);
        ULONG STDMETHODCALLTYPE AddRef();
        ULONG STDMETHODCALLTYPE Release();
		BOOL Display(char * str);
	private:
		long m_Ref;
};
#endif
