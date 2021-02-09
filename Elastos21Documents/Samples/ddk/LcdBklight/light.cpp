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
    BufferOf_<Byte, 10> ebbData;
    int nSec = 5;

    ec = CSystem::FindRunningObject(
            L"device:display0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: display, ec = 0x%08x\n", ec);
        return 1;
    }

    wprintf(L"CSystem::FindRunningObject display OK!\n");

    // turn off and on backlight

    printf("ready to turn off backlight for %d seconds.\n", nSec);
    CThread::Sleep(nSec * 1000, NULL);

    pDevice->Control(12, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    CThread::Sleep(nSec * 1000, NULL);

    pDevice->Control(11, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);


    printf("Setting brightness\n");
    CThread::Sleep(nSec * 1000, NULL);

    // set brightness
    for (int i = 0; i <= 10; i++)
    {
        printf("Level %d\n", i);
        memcpy((void *)(char *)ebbData, &i, sizeof(int));
        ebbData.SetUsed(sizeof(int));
        pDevice->Control(13, ebbData, EZBYTEBUF_NULL, NULL);
        CThread::Sleep(2 * 1000, NULL);
    }

    printf("Setting brightness done !\n");

    pDevice->Control(12, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    pDevice->Release();
    return 0;
}
