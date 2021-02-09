                           第二课
主要目的:以Dll的方式实现一个组件，调用win32函数将dll客户程序进程空间，实现客户和组件的通信
    

本课主要的内容:
服务器端：
   com组件的实现，其中包括接口、类的定义和实现，产生类的类厂的定义和实现。

   1.Server.h和server.cpp定义和实现了接口IHello和类CHello
       应主要注意IUnknown的三个成员函数QueryInterface(REFIID riid,
     void **ppvObject); AddRef();Release()的实现.
           组件clsid和接口id定义和使用


   2.ServerCF.cpp定义并实现CHello类的类厂CHelloFactory,它从IClassFactory接口派生.

   
   3.server.def描述了dll所导出的函数
     a.DllGetClassObject是Dll最重要的导出函数,每个组件Dll必须实现此函数,
       此函数由客户程序或者COM库调用,用于创建类厂,并返回类厂的接口的指针.
  
     b.DLLCanUnloadNow判断是否可从内存中卸载该组件.



客户端:
   客户程序如何使用组件.
   1.com库服务的初始化和释放
     coinitialize()
     couninitialize()
     
   2.利用win32的函数LoadLibrary,GetProcAddress,FreeLibrary显式加载DLL


   3.使用dll中的函数DllGetClassObject来创建类厂对象，再通过类厂的createinstance创建组件对象

问题：我们可以看到调用win32中的函数来转载dll,客户必须知道所需组件在哪个dll中实现，我们希望将实现组件的名称向客户隐藏起来，
     第三课将提出方法来解决它。
    
 