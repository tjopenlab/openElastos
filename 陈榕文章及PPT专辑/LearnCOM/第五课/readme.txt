                                 第五课
引言:
    前面学习了如果以dll的方式可以在进程内运行组件,如果以exe的方式则可以在进程外
运行组件,那如果我们以dll的方式能不能在以上两种方式下运行呢?

目的:
    为了实现进程内组件dll能够以进程外组件的方式来运行,我们需要实现一个dll的host。

    比较与第四课的进程外组件的不同点.本例中的host功能类似WIN NT中的
    dllhost.exe的功能.

    [host]
    1.host的主函数main()主要功能与第四课的server中主函数main()的功能基本相同.

    2.host作为一个另外的进程,既是server.dll的客户,又是client.exe的服务器.
    服务器端:
    1.由于采用dll的方式,因此在类厂的实现中,必须有导出函数DllRegisterServer和           DllUnregisterServer.

    本例程序的工作过程：
      a.客户端调用CoCreateInstance(CLSID_CHello, NULL,CLSCTX_LOCAL_SERVER,
	IID_IHello,(void **)&pHello)请求得到CLSID_CHello的IID_IHello接口。

      b.系统在COM库内存中查找是否有CLSID为CLSID_CHello的组件已在其中注册，如果
        有则直接返回给客户，否则COM系统根据CLSID_CHello在注册表中查找，并找到了
        server.dll和host.exe两个组件。

      c.因为客户端要求组件是以CLSCTX_LOCAL_SERVER的方式来运行，而server.dll以
        CLSCTX_INPROC_SERVER的方式来运行，host.exe以CLSCTX_LOCAL_SERVER的方式
       来运行，系统就会以Embedding的方式来启动host.exe。

      d.host.exe启动后，在host.exe中host.exe以客户的身份，创建server.dll中的
        组件类厂对象，并以CLSID_CHello在COM库中该注册类厂对象。
       
      e.一旦在COM库中注册了CLSID为CLSID_CHello的组件对象，系统就会把该对象返回
        给客户。这样客户就得到了该组件的类厂对象。
      
      f.host.exe进入消息循环，以等待客户。
      
      g.当客户使用完组件后，向host.exe发送WM_QUIT(用PostQuitMessage())消息。
     
      h.host.exe接收到WM_QUIT后，结束消息循环，并从COM库中注销以CLSID_CHello
        所注册的COM对象。
      
      从以上过程可以看出，host.exe作的主要工作是在COM库中以CLSID为CLSID_CHello。

         在下面的课程中，我们将以WIN NT系统中所提供的dllhost.exe来取代本课中的
      host.exe. 这样我们开发的dll方式的组件就会以CLSCTX_LOCAL_SERVER和
      CLSCTX_INPROC_SERVER 两种方式来运行，而客户程序可以不管组件到底是DLL，
      还是EXE。

    server
    1.与lesson02的server相同

    proxy
    1.与lesson03的proxy相同

    client
    1.与lesson03的client相同

    本课应掌握的重点:
    1.如何实现以dll的方式在进程内和进程外两种模式下运行.
    2.客户端是如何通过host最终实现对接口的访问.
    3.重点理解host中以CLSCTX_LOCAL_SERVER的方式运行,而server.dll则以
      CLSCTX_INPROC_SERVER的方式来运行.


