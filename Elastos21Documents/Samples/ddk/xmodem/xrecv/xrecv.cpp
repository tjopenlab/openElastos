//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <io.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\xmodem\xmodem.h"

static char *g_pBuf = NULL;
static size_t cnt = 0, len = 1024*1024*2;
static UINT modeG = 0;
int WriteFunca(const char * buffer, size_t size, size_t Cnt,ULONG f)
{
    if (modeG) {
        if(len - cnt < Cnt)
            return 0;
        memcpy(g_pBuf + cnt, buffer, Cnt);
        cnt += Cnt;
        return Cnt;
    }
    return  _write(((FILE*)f)->_file, buffer, Cnt);
}

ULONG CreateFunca(char *file, char *argv)
{
    return (ULONG)fopen(file, argv);
}

void help()
{
    printf("\rChoose a File Transfer Protocol:(Press Enter to Exit)\n \
            \r(1) Xmodem\n \
            \r(2) Xmodem-CRC\n\
            \r(3) WXmodem\n \
            \r(4) Ymodem\n \
            \r(5) YmodemG(2MB limits)\n");//packets drops too many!!!!!
}

int main(int argc, char **argv)
{
    int done, i, len;
    ECode ec;
    char ch, buffer[1030] = "./\0";
//    char villegal[] = "\"*\\<>/?:|";
//    FILE *RecvFile = NULL;
    UINT Protocol;

    if (argc < 3) {
        help();
        return 1;
    }
    ch = argv[1][0];
    strcpy(buffer, argv[2]);
    printf("argv[1] %s argv[2] %s ch %c\n", argv[1], argv[2], ch);
    Protocol = (UINT)(ch - '1');
    printf("\rYou Choose : [%c]\n", ch);
    if (Protocol == YMDMG)
        modeG = 1;
    if (Protocol < 3) {
        printf("Xmodem Protocols, You must specify a filename \n \
                \rPress Enter To Quit!\n");
    }
    else {
        printf("Ymodem Protocols, You could specify a path \n \
                \rPress Enter To Use Current Path!\n");
    }

    CXmodem *p_Xmd = new CXmodem();
    if (modeG) {
        g_pBuf = new char[1024*1024 * 2];
        if (g_pBuf == NULL) {
            printf("ModeG Buffer alloc failed!\n");
            return 1;
        }
    }
    if (NULL != p_Xmd) {
        ec = p_Xmd->XmDeviceOpen(L"device:usbser");
        if (FAILED(ec)) {
            printf("Xmodem Open Device Failed!\n");
            return 1;
        }
    }
    else {
        printf("Xmodem Protocol Init Failed!\n");
        return 1;
    }

    p_Xmd->XmDeviceSet(0);



    p_Xmd->SetHandle((void *)&CreateFunca, \
	            (void *)&WriteFunca, NULL, NULL, 0);
	done = p_Xmd->XmodemRInit(buffer, Protocol);
	memset(buffer, 0, 1030);
	if (0 != done) {
	    printf("XmodemRInit fail!\n");
	    p_Xmd->XmDeviceCls();
        delete p_Xmd;
        return 1;
	}
	printf("Receive Start.... !\n");
	while(!done) {
	    len = p_Xmd->recvStr(buffer, 1030);
	    if( len == 0 ) {
	        done = p_Xmd->XmodemRTimeout();
	        printf("XmodemRTimeout!\n");
	    }
	    else {
    	    for(i = 0; !done && i < len; ++i)
    	      done = p_Xmd->XmodemRRcv(buffer[i]);
	    }
	}
    printf("Receive Over!\n");
//exit:
    if (p_Xmd->m_file) {
        if (modeG)
	        _write(((FILE*)(p_Xmd->m_file))->_file, g_pBuf, cnt);
	    fclose((FILE*)(p_Xmd->m_file));
	}
    p_Xmd->XmDeviceCls();
    delete p_Xmd;
    if (g_pBuf)
        delete g_pBuf;
    return 0;
}


/*
    while(((ch = _getch()) != '\n' || ch != '\r')
            && (ch < '1' || ch > '5')) {
        putchar(0x08);
        putchar(' ');
        putchar(0x08);
    }
    if (ch == '\n' || ch == '\r') {
        goto exit;
    }
    Protocol = (UINT)(ch - '1');
    printf("\rYou Choose : [%c]\n", ch);
    if (Protocol == YMDMG)
        modeG = 1;
    if (Protocol < 3) {
        printf("Xmodem Protocols, You must specify a filename \n \
                \rPress Enter To Quit!\n");
    }
    else {
        printf("Ymodem Protocols, You could specify a path \n \
                \rPress Enter To Use Current Path!\n");
    }
    i = 0;
    while( i < _MAX_PATH ) {
        ch = _getch();
        if (NULL == strchr(villegal, ch)) {
            if (ch == '\n' || ch == '\r') {
                if ( i == 0 ) {
                    if (Protocol < 3)
                        goto exit;
                    else
                        break;
                }
                buffer[i] = '\0';
                break;
            }
            buffer[i] = ch;
            i++;
        }
        else {
            putchar(0x08);
            putchar(' ');
            putchar(0x08);
        }
    }
*/
