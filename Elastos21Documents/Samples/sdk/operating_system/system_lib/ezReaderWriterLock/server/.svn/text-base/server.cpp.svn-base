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
    IReaderWriterLock *pReaderWriterLock = NULL;
    IProcess *pProcess = NULL;
    WaitResult wr;
    ECode ec;

    //Create a named reader writer lock
    ec = CReaderWriterLock::New(RDWR_NAME, &pReaderWriterLock, NULL);
    if (FAILED(ec)) {
        printf("Create named reader writer lock failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Create named reader writer lock object %S\n", (wchar_t *)RDWR_NAME);

    //Acquire the reader lock
    printf("Server: Acquire the reader lock\n");
    pReaderWriterLock->ReaderLock(&wr);

    ec = CProcess::New(L"rwlock_c.exe", NULL, &pProcess);
    if (FAILED(ec)) {
        printf("Create client process failed.ec = 0x%08x\n", ec);
        goto ErrExit;
    }

    //Wait for the client find the server
    CThread::Sleep(5000, NULL);

    //Release the reader lock
    printf("Server: Release the reader lock\n");
    pReaderWriterLock->ReaderUnlock();

    //Wait for the process exit
    pProcess->WaitForExit(INFINITE, &wr);
    pProcess->Release();

ErrExit:
    if (pReaderWriterLock) {
        pReaderWriterLock->Release();
        CSystem::UnregisterRunningObject(RDWR_NAME);
    }
    return 0;
}

//==========================================================================
//Output:
//
//    Create named reader writer lock object rdwr
//    Server: Acquire the reader lock
//    Find service IReaderWriterLock.
//    Server: Release the reader lock
//    Client: Acquire the writer lock
//    Client: Release the writer lock
//==========================================================================
