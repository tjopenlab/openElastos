//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates writing data to shared
//               memory section, reading data from shared memory section.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;

    ISharedMemory *iShare;
    IProcess *iProc;

    // create shared memory
    ec = CSharedMemory::New(
        L"mysharemem",
        1024, // 1k
        TRUE,
        &iShare,
        NULL);

    if (FAILED(ec)) {
        printf("Create share memory failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("Create a share memory successfully.\n");

    // map shared memory to process
    Address addr;
    ec = iShare->Attach(MemoryProtection_RW, &addr);
    if (FAILED(ec)) {
        printf("Attach shared memory failed, ec = 0x%08x.\n", ec);
        iShare->Release();
        return -1;
    }

    // write a number to shared memory
    Int32 nMagic = 876;
    printf("Write data %d to shared memory.\n", nMagic);
    *(Int32 *)addr = nMagic;

    // create read process
    ec = CProcess::New(
        L"shareMemoryRead.exe",
        NULL,
        &iProc);

    printf("Create a process to read data in that share memory.\n");
    if (FAILED(ec)) {
        printf("Create a process failed, ec = 0x%08x.\n", ec);
        iShare->Release();
        return -1;
    }

    // wait the read process to exit
    WaitResult wr;
    ec = iProc->WaitForExit(INFINITE, &wr);
    if (SUCCEEDED(ec) && WaitResult_OK == wr) {
        printf("Read process has exited.\n");
    }

    iProc->Release();

    // remove shared memory
    ec = iShare->Detach();
    if (FAILED(ec)) {
        printf("Detach memory failed, ec = 0x%08x.\n", ec);
        iShare->Release();
        return -1;
    }

    ec = CSystem::UnregisterRunningObject(L"mysharemem");
    if (FAILED(ec)) {
        printf("Unregister service failed, ec = 0x%08x.\n", ec);
    }

    iShare->Release();

    return 0;
}

//==========================================================================
// Output:
//
//Create a share memory successfully.
//Write data 876 to shared memory.
//Create a process to read data in that share memory.
//
//==========================================================================
