                                 �����
����:
    ǰ��ѧϰ�������dll�ķ�ʽ�����ڽ������������,�����exe�ķ�ʽ������ڽ�����
�������,�����������dll�ķ�ʽ�ܲ������������ַ�ʽ��������?

Ŀ��:
    Ϊ��ʵ�ֽ��������dll�ܹ��Խ���������ķ�ʽ������,������Ҫʵ��һ��dll��host��

    �Ƚ�����ĿεĽ���������Ĳ�ͬ��.�����е�host��������WIN NT�е�
    dllhost.exe�Ĺ���.

    [host]
    1.host��������main()��Ҫ��������Ŀε�server��������main()�Ĺ��ܻ�����ͬ.

    2.host��Ϊһ������Ľ���,����server.dll�Ŀͻ�,����client.exe�ķ�����.
    ��������:
    1.���ڲ���dll�ķ�ʽ,������೧��ʵ����,�����е�������DllRegisterServer��           DllUnregisterServer.

    ��������Ĺ������̣�
      a.�ͻ��˵���CoCreateInstance(CLSID_CHello, NULL,CLSCTX_LOCAL_SERVER,
	IID_IHello,(void **)&pHello)����õ�CLSID_CHello��IID_IHello�ӿڡ�

      b.ϵͳ��COM���ڴ��в����Ƿ���CLSIDΪCLSID_CHello�������������ע�ᣬ���
        ����ֱ�ӷ��ظ��ͻ�������COMϵͳ����CLSID_CHello��ע����в��ң����ҵ���
        server.dll��host.exe���������

      c.��Ϊ�ͻ���Ҫ���������CLSCTX_LOCAL_SERVER�ķ�ʽ�����У���server.dll��
        CLSCTX_INPROC_SERVER�ķ�ʽ�����У�host.exe��CLSCTX_LOCAL_SERVER�ķ�ʽ
       �����У�ϵͳ�ͻ���Embedding�ķ�ʽ������host.exe��

      d.host.exe��������host.exe��host.exe�Կͻ�����ݣ�����server.dll�е�
        ����೧���󣬲���CLSID_CHello��COM���и�ע���೧����
       
      e.һ����COM����ע����CLSIDΪCLSID_CHello���������ϵͳ�ͻ�Ѹö��󷵻�
        ���ͻ��������ͻ��͵õ��˸�������೧����
      
      f.host.exe������Ϣѭ�����Եȴ��ͻ���
      
      g.���ͻ�ʹ�����������host.exe����WM_QUIT(��PostQuitMessage())��Ϣ��
     
      h.host.exe���յ�WM_QUIT�󣬽�����Ϣѭ��������COM����ע����CLSID_CHello
        ��ע���COM����
      
      �����Ϲ��̿��Կ�����host.exe������Ҫ��������COM������CLSIDΪCLSID_CHello��

         ������Ŀγ��У����ǽ���WIN NTϵͳ�����ṩ��dllhost.exe��ȡ�������е�
      host.exe. �������ǿ�����dll��ʽ������ͻ���CLSCTX_LOCAL_SERVER��
      CLSCTX_INPROC_SERVER ���ַ�ʽ�����У����ͻ�������Բ������������DLL��
      ����EXE��

    server
    1.��lesson02��server��ͬ

    proxy
    1.��lesson03��proxy��ͬ

    client
    1.��lesson03��client��ͬ

    ����Ӧ���յ��ص�:
    1.���ʵ����dll�ķ�ʽ�ڽ����ںͽ���������ģʽ������.
    2.�ͻ��������ͨ��host����ʵ�ֶԽӿڵķ���.
    3.�ص����host����CLSCTX_LOCAL_SERVER�ķ�ʽ����,��server.dll����
      CLSCTX_INPROC_SERVER�ķ�ʽ������.


