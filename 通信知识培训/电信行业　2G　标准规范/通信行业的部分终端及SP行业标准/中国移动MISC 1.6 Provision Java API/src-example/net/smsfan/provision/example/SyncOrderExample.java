package net.smsfan.provision.example;

import java.io.*;

import net.smsfan.provision.*;

/**
 * ����ͬ���ӿ���ʾ����<br>
 * 1.��ʼ������ͬ����SyncOrderRelation<br>
 * 2.ʵ�� SyncOrderRelationReqListener �ӿڵ�onSyncOrderRelationReq�������ɽ��յ����������xml����<br>
 * @author Joy Liu (smsfan@gmail.com)
 * @version 1.0
 */
public class SyncOrderExample implements SyncOrderRelationReqListener{

  public SyncOrderExample(int port,String serviceName) throws IOException {
    // port:�򿪵�HTTP����Ķ˿ںţ�serviceName:��������
    // ��ʼ���ɹ���misc���ط���URL:http://serverip:port/serviceName �����ύ����ͬ������
      SyncOrderRelation syncOrder = new SyncOrderRelation(port, serviceName);
      syncOrder.addListener("syncOrder",this);
  }

  /**
   * ����misc�����ύ����ͬ������,���д���,������ֻʵ�ּ򵥵���Ļ���<br>
   * ע��: xml�е�FeatureStr��ͨ��Base64�����,SyncOrderRelation�����ṩdecodeBase64�������н���<br>
   * @param xml String
   */
  public void onSyncOrderRelationReq(String xml) {
    System.out.println("Receive One SyncOrderRelation Request:");
    System.out.println(xml);
    System.out.println("--------------------------------------");
  }

  public static void main(String[] args) {
    if (args == null || args.length!=2) {
      System.out.println("Please input Server Port and Service Name");
      System.exit(0);
    }

    String port = args[0];
    if (port == null) {
      System.out.println("Please input Server Port");
      System.exit(0);
    }


    String serviceName = args[1];
    if (serviceName == null) {
      System.out.println("Please input Service Name");
      System.exit(0);
    }

    try {
      int p = Integer.parseInt(port);
      new SyncOrderExample(p, serviceName);
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
}
}
