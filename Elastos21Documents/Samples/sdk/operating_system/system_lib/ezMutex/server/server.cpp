//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了CMutex::New和CSystem::FindRunningObject
//                函数的使用。
//==========================================================================
#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define MUTEX_NAME L"mutex"

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IMutex *pMutex = NULL;
    IProcess *pProcess = NULL;
    WaitResult wr;
    //Create a named mutex
    ec = CMutex::New(MUTEX_NAME, &pMutex, NULL);
    if (FAILED(ec)) {
        fprintf(stderr, "Create named mutex failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Create named mutex object %S\n", (wchar_t *)MUTEX_NAME);

    //Create a child process
    ec = CProcess::New(L"ezmutex_c.exe", NULL, &pProcess);
    if (FAILED(ec)) {
        fprintf(stderr, "Create client process failed.ec = 0x%08x\n", ec);
        goto EXIT;
    }

    //Acquire the mutex
    pMutex->Lock(&wr);
    printf("Server: Acquire the mutex\n");

    //Release the mutex
    printf("Server: Release the mutex\n");
    pMutex->Unlock();

    //Wait for the process exit
    pProcess->WaitForExit(INFINITE, &wr);
    pProcess->Release();

EXIT:
    if (pMutex) {
        pMutex->Release();
        CSystem::UnregisterRunningObject(MUTEX_NAME);
    }
    return 0;
}

//==========================================================================
//OUTPUT:
//==========================================================================

