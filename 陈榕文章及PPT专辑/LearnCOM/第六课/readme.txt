                               ������

����:����,�����Ѿ�ѧϰ���ڲ�ͬģʽ�±�дcom�Ļ�������,����һ��Ϊ��дcom
��Ҫ�����෽���ͷʹ,��û�и����ķ�����?

        ���Ͽγ����õ���Proxy.dll,�����õ���Դ�ļ�(hello.h, hello_i.c,
    hello_p.c,dlldata.c)������MIDL.EXE����IDL�ļ����ɵģ�ֻ��һ��
    proxy.def�ļ��������Լ�д�ġ����Ҷ�ÿ������Ĵ��\�������,��*.def��
    ������ͬ��ֻ��*.def�ļ��е�LIBRARY�ֶο�����ͬ���֣�Ҳ������ͬ��

        ������˱�Թ��Ϊ��MIDL.EXE������*.defһ�������ء��ٽ�һ����Ϊ��
    MIDL.EXE���������ṩ��IDL�ļ����ɴ�һ������������Ĵ��\�������dll��
    ���ߣ���Ȼ�ù�����˱�׼������ôWindowsӦ��֪�����\�������dll������
    �������Ƿ���������е��������д����\�������dll�أ���Ȼ���\������
    ��dll�������ļ������������IDL�ļ������ģ���ζ�Žӿ�IDL�ļ������˴��\
    ��������е�Ӧ�е������Ϣ��

       �ڱ��������������Ϳ��ļ���������\������������Ϳ���ǰ����������
    ����Ϣ�Ŀ⣬Ϊ�˲������Ϳ��ļ�������IDL��ODL�������ӿڣ���������
    library�ؼ��֡�����library�ؼ��ֵ�IDL��ODL�ļ�����MIDL.EXE������
    �����Ϳ��ļ�(*.tlb)����tlb�ļ���
    
    ��������:
    1.Ϊ��ʡ��proxy��,���ǽ�hello.idl������hello"(ԭ����server)��.
      Ϊ�����������ᵽ��hello.h, hello_i.c,hello_p.c,dlldata.c,������Ҫ
      ��makefile����д����,��д��midl hello.idl.

    ����ѧϰ���ص��ǣ�
    1.���Ϳ��ļ�(tlb�ļ�)�а�����Щ�����Ϣ�������ȡ��Щ��Ϣ��

    2.�����ע�᷽����ǰ��Ŀγ��кβ�ͬ�����Ϳ��ļ����ע�ᡣ

    3.Ϊ������Windowsϵͳ�ṩ��dllhost.exeȡ�������Լ���host.exe,��ע��
      �����������дע����Ϣ��ע��CLSID,AppID, Interface��TypeLib�еı仯��
               

//----------------------------------------------------
             �÷�����Ӧ�����Ϳ⼰Windows�ṩ��ȱʡDllSurrogate����dllhost.exe��ʵ�����
  �Ľ��̼�ͽ�����ͨѶ����Ȼhello.dll�Խ����ڵ����ע�ᣬȴ�����Խ��̼��
  ���������ֹ�����ʽ��������ؼ�֮�����ڣ�

  1.�����CLSID������AppID��������ʾ:
     HKEY_CLASSES_ROOT
             |____CLSID
                    |___{ClassID}---{ (default)    REG_SZ    IHello    }
                             |      { AppID        REG_SZ    {ClassID} }
                             |
                             |___ InprocServer32             hello.dll
                             |___ TypeLib                    {LIBID}

  2.��AppID������DllSurrogate��ֵΪ��.
           HKEY_CLASSES_ROOT
             |____AppID
                    |___{ClassID}---{ (default)      REG_SZ    {ClassID} }
                                    { DllSurrogate   REG_SZ              }

    �����������Ϳ��ļ�(Hello.TLB)��Ϊ��Դ������hello.dll�ļ��У���������Դ�ļ�hello.rc��
�����·�ʽ����:
  1 typelib hello.tlb


                            ������ Build��Run

1.�����������lesson05Ŀ¼����ǰBuild���м��������������
   D:\zyc\src\LearnCOM\lesson05>zmake clean

2.Build����lesson05Ŀ¼�����������
   D:\zyc\src\LearnCOM\lesson05>zmake

3.����D:\zyc\src\LearnCOM\lesson05Ŀ¼�ľ���Ŀ¼
   D:\zyc\_ntos.dbg\LearnCOM\lesson05>�����������
   D:\zyc\src\LearnCOM\lesson05>pd ~

4.ע��hello.dll�����������
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\Hello>regcom /r D:\zyc\_ntos.dbg\
   LearnCOM\lesson05\hello\hello.dll
   
  ע����������ע�����Ϣ�������������
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\Hello>regcom /u D:\zyc\_ntos.dbg\
   LearnCOM\lesson05\hello\hello.dll

5.���пͻ��������������
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\client\client.exe

5.���н������:
    Hello, World!
                       
