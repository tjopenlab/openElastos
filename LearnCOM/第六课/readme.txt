                               第六课

引言:至此,我们已经学习了在不同模式下编写com的基本步骤,但您一定为编写com
需要面对诸多方面而头痛,有没有更简便的方法呢?

        以上课程中用到的Proxy.dll,其所用到的源文件(hello.h, hello_i.c,
    hello_p.c,dlldata.c)都是由MIDL.EXE根据IDL文件生成的，只有一个
    proxy.def文件是我们自己写的。而且对每个组件的存根\代理组件,该*.def都
    基本相同，只有*.def文件中的LIBRARY字段可以起不同名字，也可以相同。

        这就让人抱怨，为何MIDL.EXE不连该*.def一起生成呢。再进一步，为何
    MIDL.EXE不根据所提供的IDL文件，干脆一下子生成组件的存根\代理组件dll。
    或者，既然该过程如此标准化，那么Windows应该知道存根\代理组件dll所作的
    工作，是否可以让所有的组件都不写其存根\代理组件dll呢？既然存根\代理组
    件dll的所有文件都是由组件的IDL文件产生的，意味着接口IDL文件包含了存根\
    代理组件中的应有的组件信息。

       在本课中我们用类型库文件来替代存根\代理组件，类型库就是包含组件的类
    型信息的库，为了产生类型库文件可以用IDL或ODL来描述接口，并采用了
    library关键字。含有library关键字的IDL或ODL文件经过MIDL.EXE编译会产
    生类型库文件(*.tlb)，即tlb文件。
    
    服务器端:
    1.为了省掉proxy端,我们将hello.idl放在了hello"(原来的server)端.
      为了生成上述提到的hello.h, hello_i.c,hello_p.c,dlldata.c,我们需要
      在makefile中做写文章,即写明midl hello.idl.

    本课学习的重点是：
    1.类型库文件(tlb文件)中包含哪些组件信息，如何提取这些信息。

    2.组件的注册方法与前面的课程有何不同，类型库文件如何注册。

    3.为了利用Windows系统提供的dllhost.exe取代我们自己的host.exe,在注册
      表中添加了哪写注册信息。注意CLSID,AppID, Interface及TypeLib中的变化。
               

//----------------------------------------------------
             该范例是应用类型库及Windows提供的缺省DllSurrogate，即dllhost.exe，实现组件
  的进程间和进程内通讯，虽然hello.dll以进程内的组件注册，却可以以进程间和
  进程内两种工作方式工作。其关键之处在于：

  1.在类的CLSID处设置AppID；如下所示:
     HKEY_CLASSES_ROOT
             |____CLSID
                    |___{ClassID}---{ (default)    REG_SZ    IHello    }
                             |      { AppID        REG_SZ    {ClassID} }
                             |
                             |___ InprocServer32             hello.dll
                             |___ TypeLib                    {LIBID}

  2.在AppID处设置DllSurrogate的值为空.
           HKEY_CLASSES_ROOT
             |____AppID
                    |___{ClassID}---{ (default)      REG_SZ    {ClassID} }
                                    { DllSurrogate   REG_SZ              }

    本范例中类型库文件(Hello.TLB)作为资源包含在hello.dll文件中，它是在资源文件hello.rc中
用以下方式加入:
  1 typelib hello.tlb


                            第六课 Build和Run

1.可先清除整个lesson05目录的以前Build的中间结果，用以下命令：
   D:\zyc\src\LearnCOM\lesson05>zmake clean

2.Build整个lesson05目录，用以下命令：
   D:\zyc\src\LearnCOM\lesson05>zmake

3.进入D:\zyc\src\LearnCOM\lesson05目录的镜像目录
   D:\zyc\_ntos.dbg\LearnCOM\lesson05>，用以下命令：
   D:\zyc\src\LearnCOM\lesson05>pd ~

4.注册hello.dll，用以下命令：
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\Hello>regcom /r D:\zyc\_ntos.dbg\
   LearnCOM\lesson05\hello\hello.dll
   
  注：如果欲清除注册表信息，用用以下命令：
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\Hello>regcom /u D:\zyc\_ntos.dbg\
   LearnCOM\lesson05\hello\hello.dll

5.运行客户程序，用以下命令：
   D:\zyc\_ntos.dbg\LearnCOM\lesson05\client\client.exe

5.运行结果如下:
    Hello, World!
                       
