//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\xmodem\xmodem.h"

ULONG CreateFunca(char *file, char *argv)
{
    return (ULONG)fopen(file, argv);
}

int Readfile(char *buffer, size_t size, size_t Cnt,ULONG f)
{
    return  _read(((FILE*)f)->_file, buffer, Cnt);
}

ULONG Closefile(ULONG f)
{
    fclose((FILE*)f);
    return 0;
}

ULONG GetFileSize(char *file)
{
    int fh;
    ULONG fl = 0;
	fh = _open(file, _O_RDONLY );
    if( fh != -1) {
        if(_lseek(fh, 0L, SEEK_END))
            fl = _tell(fh);
        printf("file length %d\n", fl);
        _close(fh);
        return fl;
    }
    return 0;
}

void help()
{
    printf("\rChoose a File Transfer Protocol:(Press Enter to Exit)\n \
            \r(1) Xmodem\n \
            \r(2) Xmodem-CRC\n\
            \r(3) WXmodem\n \
            \r(4) Ymodem\n \
            \r(5) YmodemG\n");
}

int main(int argc, char **argv)
{
    int done, i, len;
    ECode ec;
    char ch, buffer[1024] = "./\0";
//    char villegal[] = "\"*\\<>/?:|";
    UINT Protocol;
    ULONG filelength = 0;

    if (argc < 3) {
        help();
        return 1;
    }
    ch = argv[1][0];
    strcpy(buffer, argv[2]);

    printf("argv[1] %s argv[2] %s ch %c\n", argv[1], argv[2], ch);
    Protocol = (UINT)(ch - '1');
    printf("\rYou Choose : [%c]\n", ch);
    if (Protocol < 3) {
        printf("Xmodem Protocols, You could specify a path \n \
                \rPress Enter To Quit!\n");
    }
    else {
        printf("Ymodem Protocols, You must specify a filename \n \
                \rPress Enter To Quit!\n");
    }

    CXmodem *p_Xmd = new CXmodem();
    if (NULL == p_Xmd) {
        printf("Xmodem Protocol Init Failed!\n");
        return 1;
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


    filelength = GetFileSize(buffer);
	p_Xmd->SetHandle((void *)&CreateFunca, \
	            NULL, (void *)&Readfile, (void *)&Closefile, filelength);
	done = p_Xmd->XmodemTInit(buffer, Protocol, TRUE);
    memset(buffer, 0, _MAX_PATH);
	if (0 != done) {
	    printf("XmodemRInit fail!\n");
	    p_Xmd->XmDeviceCls();
        delete p_Xmd;
        return 1;
	}

	printf("Xmit Start.... !\n");
	while(!done) {
	    len = p_Xmd->recvStr(buffer, 1024);
	    if( len == 0 ) {
	        done = p_Xmd->XmodemTTimeout();
	        printf("XmodemRTimeout!\n");
	    }
	    else {
    	    for(i = 0; !done && i < len; ++i)
    	      done = p_Xmd->XmodemTRcv(buffer[i]);
	    }
/*this use for multi file trans
	    if( done ) {
	        switch( ++filecount ) {
	            case 1:
		            done = XmodemTInit("crc.c", YMDM) != 0 ;
		            break ;
	            case 2:
		            done = XmodemTFinish();
		            break;
	            case 3:
	                break;
	        }
	    }
*/
	}
	if (done) {
	    done = p_Xmd->XmodemTFinish();
	}
    printf("Xmit Over!\n");
//exit:
    p_Xmd->XmDeviceCls();
    delete p_Xmd;
}



/*
    while(((ch = getchar()) != '\n' || ch != '\r')
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
    if (Protocol < 3) {
        printf("Xmodem Protocols, You could specify a path \n \
                \rPress Enter To Quit!\n");
    }
    else {
        printf("Ymodem Protocols, You must specify a filename \n \
                \rPress Enter To Quit!\n");
    }
    i = 0;
    while( i < 1024 ) {
        ch = getchar();
        if (NULL == strchr(villegal, ch)) {
            if (ch == '\n' || ch == '\r') {
                if ( i == 0 ) {
                    goto exit;
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



