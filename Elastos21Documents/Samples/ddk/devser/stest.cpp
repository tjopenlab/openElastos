//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

IDriver *pDevice = NULL;
int main(int argc, char *argv[])
{
    ECode ec;
    ec = CSystem::FindRunningObject(
            L"device:keypad0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        return 1;
    }

    wprintf(L"FindService OK!\n");

    //ec = pDevice->Control(5, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );

    do {
        BufferOf_<Byte, 512> ebbData;
        ec = pDevice->Read(0, 512, ebbData, NULL);
        if (FAILED(ec)) {
            printf("Read fail\n");
        }
        else {
            UINT32 * p = (UINT32 *)(char *)ebbData;
            printf("%08x, %08x\n", p[0], p[1]);
        }
    }while(0);

    pDevice->Release();

    return 0;
}
