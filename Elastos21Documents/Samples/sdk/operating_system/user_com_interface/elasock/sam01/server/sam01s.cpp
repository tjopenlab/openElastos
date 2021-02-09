//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

#define SERVER_PORT 31133
#define CLIENT_PORT 31134

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

    //setsockopt
    BOOL bOption = TRUE;
    int iOptlen = sizeof(bOption);
    if (setsockopt(slocal, SOL_SOCKET, SO_BROADCAST, (char *)&bOption, iOptlen)
        == SOCKET_ERROR) {
        printf("setsocketopt error, %d\n", WSAGetLastError());
        closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //listen
    if (listen(slocal, SOMAXCONN) != 0) {
    	printf("server listen failed, %d\n", WSAGetLastError());
        closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //accept
    SOCKET sclient;
    SOCKADDR_IN client;
    int namelen = sizeof(client);
    if ((sclient = accept(slocal, (SOCKADDR*)&client, &namelen))
        == INVALID_SOCKET) {
    	printf("server accept failed, %d\n", WSAGetLastError());
    	closesocket(slocal);
        WSACleanup();
        return -1;
    }

    //getpeername
    SOCKADDR_IN addr;
    int size = sizeof(addr);
    if (getpeername(sclient, (struct sockaddr *)&addr, &size) == SOCKET_ERROR) {
    	printf("getpeername failed, %d\n", WSAGetLastError());
    	closesocket(sclient);
    	closesocket(slocal);
    	WSACleanup();
        return -1;
    }

    //getsockname
    if (getsockname(sclient, (struct sockaddr *)&addr, &size) == SOCKET_ERROR) {
    	printf("getpeername failed, %d\n", WSAGetLastError());
    	closesocket(sclient);
    	closesocket(slocal);
    	WSACleanup();
        return -1;
    }

    //recv
    char msgrec[101];
    int iResult;
    if ((iResult = recv(sclient, msgrec, 101, 0)) == SOCKET_ERROR) {
        printf("recv failed, %d\n", WSAGetLastError());
        closesocket(slocal);
        closesocket(sclient);
        WSACleanup();
        return -1;
    }
    else {
        printf("recv : %s, %d characters\n", msgrec, iResult);
    }

    //closesocket
    closesocket(slocal);
    closesocket(sclient);

    //WSACleanup
    WSACleanup();
    return 0;
}
