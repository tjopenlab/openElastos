package net.smsfan.provision.example;

import net.smsfan.provision.SubscribeRequest;

/**
 * 反响订购/取消接口演示代码<br>
 * @author Joy Liu (smsfan@gmail.com)
 * @version 1.0
 */
public class SubscribeExample {

  public SubscribeExample() {
  }

  public static void main(String[] args) {
    if (args == null || args.length != 1) {
      System.out.println("Please input dest url");
      System.exit(0);
    }

    String url = args[0];
    if (url == null) {
      System.out.println("Please input dest url");
      System.exit(0);
    }

    SubscribeRequest req = new SubscribeRequest(url);
    req.sendSubscribe("13800000000","13800000000","-ABCD","900128","999");
    req.sendUnSubscribe("13800000000","13800000000","-ABCD","900128","999");
  }

}
