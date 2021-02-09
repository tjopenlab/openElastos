//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <stdio.h>
#include <elastos.h>
#include <winsock.h>

typedef char *caddr_t;

#if 0
struct  ifreq {
#define IFNAMSIZ 16
    char    ifr_name[IFNAMSIZ];     /* if name, e.g. "en0" */
    union {
        struct  sockaddr ifru_addr;
        struct  sockaddr ifru_dstaddr;
        struct  sockaddr ifru_broadaddr;
        short   ifru_flags[2];
        short   ifru_index;
        int ifru_metric;
        int ifru_mtu;
        int ifru_phys;
        int ifru_media;
        caddr_t ifru_data;
        int ifru_cap[2];
    } ifr_ifru;

#define ifr_addr    ifr_ifru.ifru_addr  /* address */
#define ifr_dstaddr ifr_ifru.ifru_dstaddr   /* other end of p-to-p link */
#define ifr_broadaddr   ifr_ifru.ifru_broadaddr /* broadcast address */
#define ifr_flags   ifr_ifru.ifru_flags[0]  /* flags (low 16 bits) */
#define ifr_flagshigh   ifr_ifru.ifru_flags[1]  /* flags (high 16 bits) */
#define ifr_metric  ifr_ifru.ifru_metric    /* metric */
#define ifr_mtu     ifr_ifru.ifru_mtu   /* mtu */
#define ifr_phys    ifr_ifru.ifru_phys  /* physical wire */
#define ifr_media   ifr_ifru.ifru_media /* physical media */
#define ifr_data    ifr_ifru.ifru_data  /* for use by interface */
#define ifr_reqcap  ifr_ifru.ifru_cap[0]    /* requested capabilities */
#define ifr_curcap  ifr_ifru.ifru_cap[1]    /* current capabilities */
#define ifr_index   ifr_ifru.ifru_index /* interface index */
};
#endif
#define SIOCGIFADDR _IOWR('i',33, struct ifreq) /* get ifnet address */


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

    ifreq getAddr;
    long cmd;

    cmd = SIOCGIFADDR;
    memset(&getAddr, 0, 20);
    strncpy((char*)&getAddr, "lo0", 20);
    if (ioctlsocket(slocal, cmd, (unsigned long*)&getAddr) == SOCKET_ERROR) {
        printf("ioctlsocket failed, %d\n", WSAGetLastError());
    }
    else {
        printf("ioctlsocket success!\n");
    }

    closesocket(slocal);
    WSACleanup();
    return 0;
}
