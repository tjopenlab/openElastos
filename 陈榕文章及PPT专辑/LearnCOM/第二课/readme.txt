                           �ڶ���
��ҪĿ��:��Dll�ķ�ʽʵ��һ�����������win32������dll�ͻ�������̿ռ䣬ʵ�ֿͻ��������ͨ��
    

������Ҫ������:
�������ˣ�
   com�����ʵ�֣����а����ӿڡ���Ķ����ʵ�֣���������೧�Ķ����ʵ�֡�

   1.Server.h��server.cpp�����ʵ���˽ӿ�IHello����CHello
       Ӧ��Ҫע��IUnknown��������Ա����QueryInterface(REFIID riid,
     void **ppvObject); AddRef();Release()��ʵ��.
           ���clsid�ͽӿ�id�����ʹ��


   2.ServerCF.cpp���岢ʵ��CHello����೧CHelloFactory,����IClassFactory�ӿ�����.

   
   3.server.def������dll�������ĺ���
     a.DllGetClassObject��Dll����Ҫ�ĵ�������,ÿ�����Dll����ʵ�ִ˺���,
       �˺����ɿͻ��������COM�����,���ڴ����೧,�������೧�Ľӿڵ�ָ��.
  
     b.DLLCanUnloadNow�ж��Ƿ�ɴ��ڴ���ж�ظ����.



�ͻ���:
   �ͻ��������ʹ�����.
   1.com�����ĳ�ʼ�����ͷ�
     coinitialize()
     couninitialize()
     
   2.����win32�ĺ���LoadLibrary,GetProcAddress,FreeLibrary��ʽ����DLL


   3.ʹ��dll�еĺ���DllGetClassObject�������೧������ͨ���೧��createinstance�����������

���⣺���ǿ��Կ�������win32�еĺ�����ת��dll,�ͻ�����֪������������ĸ�dll��ʵ�֣�����ϣ����ʵ�������������ͻ�����������
     �����ν�����������������
    
 