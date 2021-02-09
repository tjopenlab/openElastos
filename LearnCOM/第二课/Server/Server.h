#include <stdio.h>
#include <unknwn.h>	
#ifndef _SERVER_H_
#define _SERVER_H_	

//IHello接口的ID,此ID可由UUIDGEN.EXE或GUIDGen.exe工具产生.
const IID IID_IHello = 
    {0xe385b4d6, 0xc6b2,0x4cbb,{0xa3,0x43,0x04,0x3e,0xff,0x26,0x2c,0xa1}};

//CHello类的 clsid,此clsid可由UUIDGEN.EXE或GUIDGen.exe工具产生.
const CLSID CLSID_CHello=
    {0x3fbb0c4f, 0xced5, 0x45aa, {0x9a,0xb0,0x91,0xf1,0xa7,0xbe,0x68,0x70}};

//
//  功能： IHello接口定义.
//         因为IUnknown接口已经在unknwn.h文件中实现,故不用再定义IUnknown接口
//         任何COM接口都应该直接或简捷从IUnknown派生.接口定义只定义COM的接口
//         结构,并没有具体的实现, 由于C++的vtable结构与COM接口结构完全以一致,
//         因此采用C++定义COM接口较为简洁. C语言的接口
//	       定义方法可参见<<COM原理与应用>>中的第27页.
//
class IHello: public IUnknown //define  IHello interface's structure 
{
	public:
		virtual BOOL  Display(char * str)=0;//定义为纯虚函数
};

//
//  功能： CHello类结构定义.
//        CHello从IHello公有派生,是IHello接口的具体实现.
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
