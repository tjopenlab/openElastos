//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CONV(PTR, EBUF)  ((PTR)((char*)EBUF))
#define SETBUF(TYPE, NUM, EBUF) (EBUF.SetUsed(sizeof(TYPE) * NUM))
#define LOADBUF(EBUF) (EBUF.Used())

void __cdecl outs(char* buf, int buflen)
{
    printf("\n");
    int linCnt = buflen >> 4;
    int line, clum = 0;
    for (line = 0; line < linCnt; line++) {
        printf("%04x\t", line*0x10);
        for(clum = 0; clum < 0x10; clum++)
            printf("%02x ", buf[line*0x10+clum]);
        printf("\n");
    }
    printf("line number : %d, clum : %d, Bytes : %d\n",
        line, clum, line*clum);
}

int main()
{
    IDriver *pDevice = NULL;
    ECode ec = NOERROR;
    UINT CntWt;
    BufferOf_<Byte, 512> OutBuf;
    UCHAR *OutData = CONV(UCHAR*, OutBuf);

    ec = CSystem::FindRunningObject(
            L"device:minisdbus", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: minisd, ec = 0x%08x\n", ec);
        goto __Exit;
    }
    memset(OutData, 'a', 512);
    SETBUF(UCHAR, 512, OutBuf);
    ec = pDevice->Write(0, OutBuf, &CntWt, NULL);
    if (FAILED(ec)) {
        printf("ERROR:write minisd Failed!\n");
        goto __Exit;
    }
    printf("Init New Mini SD Card Successfully!\n");


__Exit:
    if (NULL != pDevice) {
        pDevice->Release();
    }

    return 0;
}

