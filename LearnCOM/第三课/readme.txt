                            ������
���ԣ�ͬ����Dll�ķ�ʽʵ��һ��������ÿ��ԵǼ�ע���ķ�ʽ�����߿ͻ��������dll��������Ϣ
��Ҫ���ݣ�
    
    1.��ν����ע�ᵽϵͳע�����

      a. DLL����Ҫʵ��ע�Ṧ��,�����Ҫ����������������:
         DllRegistryServer ��ע�����ע�����
         DllUnRegistryServer ��ע�����ɾ�����ע����Ϣ
         ����def�ļ���������������������.
      b. ��makefile.inc�е���REGSVR32.exe���� 
      c. REGSVR32.exe����ʵ���ϵ���������������������������ע��.  

    2.��ͬ��ʽ�����೧��ע�����ǵ�����

      a. �Ͻڿοͻ�����ֱ�ӵ���dll�ĵ�������DllGetclassObject�������೧
      b. ��ڿ��ǵ���com��Ŀ⺯��CoGetClassObject�������೧
         ��ʵCoGetClassObject�����е�����DllGetclassObject
         ע��CoGetClassObject�ĵ���������dwClsContext,��������������ϣ�
               CLSCTX_INPROC_SERVER �ͻ�ϣ������ͬһ���������е����
               CLSCTX_LOCAL_SERVER �ͻ�ϣ��������ͬһ̨������ͬ���������е����
               CLSCTX_REMOTE_SERVER �ͻ�ϣ��������Զ�̻������е����
         ������ʹ����CLSCTX_INPROC_SERVER,������Ӧʹ��dll����
���⣺
    ��ȻCoGetClassObject����֧�ֲ�ͬ��ʽ���е��������һ�����ǽ�ʹ��EXE�������
