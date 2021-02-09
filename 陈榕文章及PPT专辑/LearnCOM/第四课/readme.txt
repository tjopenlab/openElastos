                            第四课
引言：前面都以dll方式来实现组件，该课以exe的方式实现一个组件，请注意不同点。
     
   
本课主要的内容:
    如果服务器是在dll中，com系统就能动态的装载服务器动态连接库到客户进程空间，
实现客户和组件间的无缝连接。但如果组件是exe形式，客户就要和一种特殊的对象，代理
（proxy）打交道。从客户观点看，
    服务器端   
   1.定义接口IHello的实现类CHello和类厂(参见Server.h).
     a.定义一个IHello的具体实现的类CHello,它从IHello接口派生.
     b.定于类厂CHelloFactory,它从IClassFactory接口派生.
      这个步骤中的主要内容与第二课相同，但IHello接口结构的定义是由IDL来描述的，
     并由MIDL.EXE生成hello.h.(注意MIDL.EXE的使用方法---MIDL.EXE /?)

   2.由于进程外组件不是Dll,没有导出函数DllRegisterServer和DllUnregisterServer,
     组件必须支持自注册,即在主函数main()要有注册功能(用RegisterExe()实现)和
     卸载功能(用UnRegisterExe()实现).注意应该在注册表中添加哪些内容。

   3.编写主函数main(),其主要工作过程是根据用户提供的命令行信息,决定是否注册组
     件,卸载组件,还是运行组件.如果是运组件则，这先创建类厂对象，然后在COM库中
     注册组件，进入消息循环，等待客户端的请求, 当用户不再使用组件时从COM库中
     删除组件.
     特别注意CoRegisterClassObject和CoRevokeClassObject的主要功能.

    存根\代理组件
   1.用IDL来描述接口,注意关键字的用法及含义，例如（import,object,uuid,
     interface,coclass等）。

   2.用MIDL.EXE编译用IDL描述的接口IDL文件,产生hello.h, hello_i.c, hello_p.c,
     dlldata.c四个文件. MIDL.EXE的帮助请看MSDN.

   3.编写.def文件,如proxy.def.

   4.用.def文件和MIDL.EXE编译IDL文件产生的四个文件,即proxy.def,hello.h,
     hello_i.c, hello_p.c, dlldata.c, proxy.def一起生成存根\代理组件.

   5.注册存根\代理组件.方法:regsvr32 [path]\proxy.dll.

    客户端
   1.获取并使用组件的接口,先用CoCreateInstance()获取组件的特定接口指针，并调用
     此接口所提供的功能.

   应达到的目标:
   1.掌握以exe方式实现的COM组件的基本组成及实现。包括组件本身和类厂接口中的各个
     成员函数是如何实现的。
     特别与DLL方式不同的是exe方式实现的组件需要存根\代理组件来实现不同进程间数
     据的Marshal与UnMarshal.
      
   2.掌握如何用IDL来描述组件的接口。

   3.掌握如何用MIDL.EXE来编译IDL文件，并生成相应的.h和.c文件。

   4.掌握用EXE方式实现的组件与用DLL方式实现的组件的工作过程不同之处。
