//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program whows how to use methods of CSystem::FindRunningObject
//                and CReaderWriterLock::New.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define RDWR_NAME L"rdwr"

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IReaderWriterLock *pReaderWriterLock = NULL;
    WaitResult wr;
    //Find the registered IReaderWriterLock interface
    ec = CSystem::FindRunningObject(RDWR_NAME, (IInterface **)&pReaderWriterLock);
    if (FAILED(ec)) {
        printf("Find service reader writer lock failed. ec = 0x%08x\n", ec);
        return -1;
    }


    printf("Find service IReaderWriterLock.\n");

    //Acquire the writer lock
    pReaderWriterLock->WriterLock(&wr);
    printf("Client: Acquire the writer lock\n");
    //Release the writer lock
    pReaderWriterLock->WriterUnlock();
    printf("Client: Release the writer lock\n");

    pReaderWriterLock->Release();
    return 0;
}
