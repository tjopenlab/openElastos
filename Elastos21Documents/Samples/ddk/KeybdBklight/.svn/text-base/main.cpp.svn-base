//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================



#include <elastos.h>
#include <stdio.h>


IDriver * pDevice;

int main(int argc, char ** argv)
{
    ECode ec;
    int nType = 0;

    ec = CSystem::FindRunningObject(
            L"device:keypad0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: keypad, ec = 0x%08x\n", ec);
        return 1;
    }

    printf("Ready to turn on backlight\n");

    CThread::Sleep(5000, NULL);

    // turn on backlight
    pDevice->Control(1001, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    printf("Ready to turn off backlight\n");
    CThread::Sleep(5000, NULL);

    pDevice->Control(1000, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    CThread::Sleep(5000, NULL);

    printf("LED Test\n");


    /*
    enum LEDStyle
    {
        LS_Off          = 0,
        LS_Green        = 1,
        LS_Red          = 2,
        LS_RedBlink     = 3,
        LS_GreenBlink   = 4
    };
    */
    BufferOf<Byte> ebbData = BufferOf<Byte>::AllocByteBuf(10);
    ebbData.SetUsed(sizeof(int));

    printf("LED Off\n");
    nType = 0;
    memcpy((void *)(char *)ebbData, &nType, sizeof(int));
    pDevice->Control(15, ebbData, EZBYTEBUF_NULL, NULL);
    CThread::Sleep(5000, NULL);

    printf("LED Green\n");
    nType = 1;
    memcpy((void *)(char *)ebbData, &nType, sizeof(int));
    pDevice->Control(15, ebbData, EZBYTEBUF_NULL, NULL);
    CThread::Sleep(5000, NULL);

    printf("LED Red\n");
    nType = 2;
    memcpy((void *)(char *)ebbData, &nType, sizeof(int));
    pDevice->Control(15, ebbData, EZBYTEBUF_NULL, NULL);
    CThread::Sleep(5000, NULL);

    printf("LED RedBlink\n");
    nType = 3;
    memcpy((void *)(char *)ebbData, &nType, sizeof(int));
    pDevice->Control(15, ebbData, EZBYTEBUF_NULL, NULL);
    CThread::Sleep(5000, NULL);

    printf("LED GreenBlink\n");
    nType = 4;
    memcpy((void *)(char *)ebbData, &nType, sizeof(int));
    pDevice->Control(15, ebbData, EZBYTEBUF_NULL, NULL);
    CThread::Sleep(5000, NULL);


    // free resource
    pDevice->Release();
    BufferOf<Byte>::FreeByteBuf(ebbData);

    return 0;
}


