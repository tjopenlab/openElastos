//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

#define SERVER_PORT 52103
#define CLIENT_PORT 52104

#define CLIENT_IP "192.168.2.50"

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
    local.sin_port = htons(SERVER_PORT);
    local.sin_family = AF_INET;
    if (bind(slocal, (SOCKADDR *)&local, sizeof(local)) != 0) {
        printf("bind failed!\n");
        closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //connect
    SOCKADDR_IN client;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);
    client.sin_family = AF_INET;
    int namelen = sizeof(client);
    if (connect(slocal, (SOCKADDR*)&client, namelen) != 0) {
    	printf("connect failed, %d\n", WSAGetLastError());
    	closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //recvfrom
    char msgrec[101];
    if (recvfrom(slocal, msgrec, 101, 0, (SOCKADDR*)&client, &namelen)
        == SOCKET_ERROR) {
        printf("recvfrom failed, %d\n", WSAGetLastError());
        closesocket(slocal);
        WSACleanup();
        return -1;
    }
    else {
        printf("recv message : %s\n", msgrec);
    }

    closesocket(slocal);
    WSACleanup();
    return 0;
}
