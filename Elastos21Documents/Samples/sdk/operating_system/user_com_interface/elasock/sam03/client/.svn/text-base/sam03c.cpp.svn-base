//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

#define SERVER_PORT 52103
#define CLIENT_PORT 52104

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
    if ((slocal = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) == INVALID_SOCKET) {
        //WSAGetLastError
        printf("create socket error, %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    //bind
    SOCKADDR_IN local;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(CLIENT_PORT);
    local.sin_family = AF_INET;
    if (bind(slocal, (SOCKADDR *)&local, sizeof(local)) != 0) {
        printf("bind failed!\n");
        closesocket(slocal);
        WSACleanup();
        return -1;
    }

    SOCKADDR_IN server;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);
    server.sin_family = AF_INET;
    int namelen = sizeof(server);

    //sendto
    char msgsend[] = "message from client";
    int iResult;
    iResult = sendto(slocal, msgsend, sizeof(msgsend) + 1, 0,
        (SOCKADDR*)&server, namelen);
    if (iResult == SOCKET_ERROR) {
    	printf("sendto failed, %d\n", WSAGetLastError());
    	closesocket(slocal);
        WSACleanup();
        return -1;
    }
    else {
    	printf("sendto success!\n");
    }

    closesocket(slocal);
    WSACleanup();
    return 0;
}
