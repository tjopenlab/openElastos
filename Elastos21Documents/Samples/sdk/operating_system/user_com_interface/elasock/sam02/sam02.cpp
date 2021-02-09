//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

const char addr[] = {(char)0xc0, (char)0xa8, (char)0x0, (char)0x1};//192.168.0.1
const char* name = "bbs.tsinghua.edu.cn";

EXTERN_C int main(int argc, char * argv[])
{
	WSADATA wsd;

    //WSAStartup
    if (WSAStartup(0x0101, &wsd) != 0) {
        printf("WSAStartup failed!\n");
        return -1;
    }

    //gethostbyaddr
    struct hostent * host1;
    if ((host1 = gethostbyaddr(addr, 4, AF_INET)) == NULL) {
        printf("gethostbyaddr error, %d\n", WSAGetLastError());
    }
    else {
        printf("gethostbyaddr ok\n");
    }

    //gethostbyname
    struct hostent * host2;
    if ((host2 = gethostbyname(name)) == NULL){
        printf("gethostbyname error, %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    else {
        printf("gethostbyname ok\n");
    }

    //gethostname
    char hostname[20];
    if (!gethostname(hostname, 20)) {
        printf("gethostname ok\n");
    }
    else {
        printf("gethostname error, %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //WSACleanup
    WSACleanup();

    return 0;
}
