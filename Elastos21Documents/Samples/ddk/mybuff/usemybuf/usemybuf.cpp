//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <stdio.h>
#include <string.h>
#include <elastos.h>
using namespace Elastos;

#define DEV_NAME0 L"device:MyBuff0"
#define DEV_NAME1 L"device:MyBuff1"
#define DATA      "Hello, World!"

void UseMyBuff0()
{
    ECode ec;
    IDeviceDriver *pDriver = NULL;
    UInt32 len = strlen(DATA) + 1;
    PMemoryBuf pebbData = MemoryBuf::Alloc(len);

    ec = CSystem::FindRunningObject(
	    DEV_NAME0, (IInterface **)&pDriver);
    if (FAILED(ec)) {
        printf("Get IDeviceDriver failed\n");
        goto Exit;
    }

    pebbData->Copy((Byte *)DATA, len);

    ec = pDriver->Write(0, *pebbData, 0, 0);
    if (FAILED(ec)) {
        printf("Write Data failed.\n");
        goto Exit;
    }

    pebbData->SetUsed(0);
    ec = pDriver->Read(0, len, pebbData, 0);
    if (FAILED(ec)) {
        printf("Read Data failed.\n");
        goto Exit;
    }

    printf("Data: %s\n", pebbData->GetPayload());

Exit:
    if (pDriver)
        pDriver->Release();

    MemoryBuf::Free(pebbData);
}

void UseMyBuff1()
{
    ECode ec;
    int size;
    IDeviceDriver *pDriver = NULL;
    MemoryBuf_<4> ebbData1;
    MemoryBuf_<4> ebbData2;

    ec = CSystem::FindRunningObject(
	    DEV_NAME1, (IInterface **)&pDriver);
   if (FAILED(ec)) {
        printf("Get IDeviceDriver failed\n");
        goto Exit;
    }

    ec = pDriver->Control(0, ebbData1, &ebbData2, 0);

    if (FAILED(ec)) {
        printf("Control IDeviceDriver failed\n");
        goto Exit;
    }
    printf("MyBuff1 Size: %d\n", *(unsigned long*)ebbData2.GetPayload());

    ebbData2.SetUsed(0);
    size = 512;
    ebbData1.Copy((Byte *)&size, sizeof(int));
    ec = pDriver->Control(1, ebbData1, &ebbData2, 0);

    if (FAILED(ec)) {
        printf("Control IDeviceDriver failed\n");
        goto Exit;
    }
    printf("MyBuff1 Size: %d\n", *(unsigned long*)ebbData2.GetPayload());

Exit:
    if (pDriver)
        pDriver->Release();
}

int main()
{
    UseMyBuff0();
    UseMyBuff1();

    return 0;
}

