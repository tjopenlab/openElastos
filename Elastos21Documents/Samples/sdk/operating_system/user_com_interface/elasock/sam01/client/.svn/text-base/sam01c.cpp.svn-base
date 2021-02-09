//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

#define SERVER_PORT 31133
#define CLIENT_PORT 31134

#define SERVER_IP "192.168.2.38"

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
        printf("create socket error, %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    //bind
    SOCKADDR_IN local;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(SERVER_PORT);
    local.sin_family = AF_INET;
    if (bind(slocal, (SOCKADDR *)&local, sizeof(local)) != 0) {
        printf("bind socket failed, %d\n", WSAGetLastError());
        closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //connect
    SOCKADDR_IN server;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);
    server.sin_family = AF_INET;
    if (connect(slocal, (SOCKADDR*)&server, sizeof(server)) != 0) {
        printf("connect failed, %d\n", WSAGetLastError());
    	closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //send
    char msgsend[] = "Message from client";
    if (send(slocal, msgsend, sizeof(msgsend) + 1, 0) == SOCKET_ERROR) {
    	printf("send failed, %d\n", WSAGetLastError());
    	closesocket(slocal);
        WSACleanup();
        return -1;
    }
    else {
    	printf("send success!\n");
    }

    //closesocket
    closesocket(slocal);

    //WSACleanup
    WSACleanup();

    return 0;
}
