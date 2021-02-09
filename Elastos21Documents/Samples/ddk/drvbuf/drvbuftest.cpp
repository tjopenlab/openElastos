//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <display.h>
#include <camera.h>

static IDriver * s_pIDrvBuf;

// Flags for Driver buffer alloc
#define DRVBUF_SPEED_FAST   0x1
#define DEVBUF_REALLOC_COPY 0x2
EXTERN_C void * Drv_AllocBuffer(uint_t uPages, uint_t uFlag)
{
    BufferOf_<Byte, 8> ebbInBuf;
    BufferOf_<Byte, 4> ebbOutBuf;

    *(uint_t *)(char *)ebbInBuf = uPages;
    *((uint_t *)(char *)ebbInBuf + 1) = uFlag;
    ebbInBuf.SetUsed(8);

    s_pIDrvBuf->Control(0, ebbInBuf, ebbOutBuf, NULL);

    return (*(void * *)(char *)ebbOutBuf);
}

EXTERN_C void * Drv_ReallocBuffer(void * VirtAddr, uint_t uOldPages,
    uint_t uNewPages, uint_t uFlag)
{
    BufferOf_<Byte, 16> ebbInBuf;
    BufferOf_<Byte, 4> ebbOutBuf;

    *(void * *)(char *)ebbInBuf = VirtAddr;
    *((uint_t *)(char *)ebbInBuf + 1) = uOldPages;
    *((uint_t *)(char *)ebbInBuf + 2) = uNewPages;
    *((uint_t *)(char *)ebbInBuf + 3) = uFlag;
    ebbInBuf.SetUsed(16);

    s_pIDrvBuf->Control(1, ebbInBuf, ebbOutBuf, NULL);

    return (*(void * *)(char *)ebbOutBuf);
}

EXTERN_C void Drv_FreeBuffer(void * VirtAddr, uint_t uPages)
{
    BufferOf_<Byte, 8> ebbInBuf;

    *(void * *)(char *)ebbInBuf = VirtAddr;
    *((uint_t *)(char *)ebbInBuf + 1) = uPages;
    ebbInBuf.SetUsed(8);

    s_pIDrvBuf->Control(2, ebbInBuf, EZBYTEBUF_NULL, NULL);

}

int main(int argc, char *argv[])
{
    int *pBuffer;

    ECode ec = CSystem::FindRunningObject(
            L"device:drvbuf", (IInterface **)&s_pIDrvBuf);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: drvbuf, ec = 0x%08x\n", ec);
        return 1;
    }

    pBuffer = (int *)Drv_AllocBuffer(1, 0);
    printf("1 pBuffer=0x%08x\n", pBuffer);
    if (!pBuffer) goto Error;

    *pBuffer = 0x12345678;
    pBuffer = (int *)Drv_ReallocBuffer(pBuffer, 1, 5, DEVBUF_REALLOC_COPY);
    printf("2 pBuffer=0x%08x\n", pBuffer);
    if (!pBuffer) goto Error;
    printf("2 *pBuffer=0x%08x\n", *pBuffer);

    *pBuffer = 0x80868088;
    pBuffer = (int *)Drv_ReallocBuffer(pBuffer, 5, 2,
        DRVBUF_SPEED_FAST | DEVBUF_REALLOC_COPY);
    printf("3 pBuffer=0x%08x\n", pBuffer);
    if (!pBuffer) goto Error;
    printf("3 *pBuffer=0x%08x\n", *pBuffer);

    *pBuffer = 0x567890ab;
    pBuffer = (int *)Drv_ReallocBuffer(pBuffer, 2, 2, 0);
    printf("4 pBuffer=0x%08x\n", pBuffer);
    if (!pBuffer) goto Error;
    printf("4 *pBuffer=0x%08x\n", *pBuffer);

    *pBuffer = 0x88888888;
    pBuffer = (int *)Drv_ReallocBuffer(pBuffer, 2, 32, DEVBUF_REALLOC_COPY);
    printf("5 pBuffer=0x%08x\n", pBuffer);
    if (!pBuffer) goto Error;
    printf("5 *pBuffer=0x%08x\n", *pBuffer);

    Drv_FreeBuffer(pBuffer, 32);

    return 0;

Error:
    return 1;
}
