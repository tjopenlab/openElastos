                            第三课
引言：同样以Dll的方式实现一个组件，该课以登记注册表的方式来告诉客户程序组件dll的有用信息
主要内容：
    
    1.如何将组件注册到系统注册表中

      a. DLL本身要实现注册功能,因此它要导出如下俩个函数:
         DllRegistryServer 在注册表中注册组件
         DllUnRegistryServer 在注册表中删除组件注册信息
         并在def文件中添入这俩个导出函数.
      b. 在makefile.inc中调用REGSVR32.exe程序 
      c. REGSVR32.exe程序实际上调用了上述俩个函数来完成组件的注册.  

    2.不同方式创建类厂，注意它们的区别

      a. 上节课客户程序直接调用dll的导出函数DllGetclassObject来创建类厂
      b. 这节课是调用com库的库函数CoGetClassObject来创建类厂
         其实CoGetClassObject函数中调用了DllGetclassObject
         注意CoGetClassObject的第三个参数dwClsContext,它可能有如下组合：
               CLSCTX_INPROC_SERVER 客户希望创建同一进程中运行的组件
               CLSCTX_LOCAL_SERVER 客户希望创建在同一台机器不同进程中运行的组件
               CLSCTX_REMOTE_SERVER 客户希望创建在远程机器运行的组件
         该例中使用了CLSCTX_INPROC_SERVER,因此组件应使用dll发布
问题：
    既然CoGetClassObject函数支持不同方式运行的组件，下一课我们将使用EXE运行组件
