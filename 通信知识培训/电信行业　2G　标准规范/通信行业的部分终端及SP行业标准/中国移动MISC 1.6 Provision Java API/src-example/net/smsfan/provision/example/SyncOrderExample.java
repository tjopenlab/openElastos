package net.smsfan.provision.example;

import java.io.*;

import net.smsfan.provision.*;

/**
 * 正向同步接口演示代码<br>
 * 1.初始化正向同步类SyncOrderRelation<br>
 * 2.实现 SyncOrderRelationReqListener 接口的onSyncOrderRelationReq方法即可接收到正向请求的xml数据<br>
 * @author Joy Liu (smsfan@gmail.com)
 * @version 1.0
 */
public class SyncOrderExample implements SyncOrderRelationReqListener{

  public SyncOrderExample(int port,String serviceName) throws IOException {
    // port:打开的HTTP服务的端口号，serviceName:服务名称
    // 初始化成功后，misc网关访问URL:http://serverip:port/serviceName 即可提交正向同步数据
      SyncOrderRelation syncOrder = new SyncOrderRelation(port, serviceName);
      syncOrder.addListener("syncOrder",this);
  }

  /**
   * 接收misc网关提交正向同步数据,进行处理,本函数只实现简单的屏幕输出<br>
   * 注意: xml中的FeatureStr是通过Base64编码的,SyncOrderRelation类中提供decodeBase64方法进行解码<br>
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
