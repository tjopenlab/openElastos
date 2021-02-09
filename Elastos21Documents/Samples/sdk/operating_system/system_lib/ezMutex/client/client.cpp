//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//===========================================================================
// Description  : ���������ʾ��CMutex::New��CSystem::FindRunningObject
//                ������ʹ�á�
//===========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define MUTEX_NAME L"mutex"

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IMutex *pMutex = NULL;
    WaitResult wr;

    //Find the registered IMutex interface
    ec = CSystem::FindRunningObject(MUTEX_NAME, (IInterface **)&pMutex);
    if (FAILED(ec)) {
        fprintf(stderr, "Find service mutex failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Find service IMutex\n");

    //Acquire the mutex
    pMutex->Lock(&wr);
    printf("Client: Acquire the mutex\n");

    //Release the mutex
    printf("Client: Release the mutex\n");
    pMutex->Unlock();

    pMutex->Release();
    return 0;
}
