//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

#define SERVER_PORT 2126

EXTERN_C int main(int argc, char * argv[])
{
    WSADATA wsd;
    int i;

    //WSAStartup
    if (WSAStartup(0x0101, &wsd) != 0) {
        printf("WSAStartup failed!\n");
        return -1;
    }

    fd_set* socket_set = NULL;
    SOCKET s[5];
    TIMEVAL tv = {0, 0};
    FD_ZERO(socket_set);


    for (i = 0; i < 5; i++) {
        if ((s[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == INVALID_SOCKET) {
            printf("create socket error, %d\n", WSAGetLastError());
            WSACleanup();
            return -1;
        }
        else {
            FD_SET(s[i], socket_set);
        }
    }

    //bind
    SOCKADDR_IN local;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(SERVER_PORT);
    local.sin_family = AF_INET;
    if (bind(s[2], (SOCKADDR *)&local, sizeof(local)) != 0) {
        printf("bind failed, %d\n", WSAGetLastError());
        goto Exit;
    }

    //listen
    if (listen(s[2], SOMAXCONN) != 0) {
    	printf("listen failed, %d\n", WSAGetLastError());
        goto Exit;
    }

    if (select(1, socket_set, NULL, NULL, &tv) == SOCKET_ERROR) {
        printf("select error, %d\n", WSAGetLastError());
        goto Exit;
    }
    else {
        printf("select success");
    }

Exit:
    for (i = 0; i < 5; i++) {
        closesocket(s[i]);
    }

    delete socket_set;
    socket_set = NULL;

    WSACleanup();

    return 0;
}
