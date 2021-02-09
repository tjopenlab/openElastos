//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

//#define TCP_MAXSEG  0x02

EXTERN_C int main(int argc, char* argv[])
{
    WSADATA wsd;

    //WSAStartup
    if (WSAStartup(0x0101, &wsd) != 0) {
        printf("WSAStartup failed!\n");
        return -1;
    }

    //socket
    SOCKET slocal;
    if ((slocal = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == INVALID_SOCKET) {
        //WSAGetLastError
        printf("create socket error, %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    //getsockopt
    int optval;
    int len = sizeof(int);
    if (getsockopt(slocal, IPPROTO_TCP, TCP_MAXSEG, (char*)&optval,
        &len) == SOCKET_ERROR) {
        printf("getsockopt failed, %d\n", WSAGetLastError());
    }

    //shutdown
    if (shutdown(slocal, SD_SEND) != 0) {
        printf("shutdown failed, %d\n", WSAGetLastError());
    }

    closesocket(slocal);
    WSACleanup();
    return 0;
}
