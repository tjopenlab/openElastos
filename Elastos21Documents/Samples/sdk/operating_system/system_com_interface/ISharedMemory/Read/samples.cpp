//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description : The following example demonstrates reading data from shared
//               memory section.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    ISharedMemory *iShare = NULL;

    // Get ther service name
    ec = CSystem::FindRunningObject(L"mysharemem", (IInterface **)&iShare);
    if (FAILED(ec)) {
        printf("Get shared memory failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // map shared memory to address space.
    Address addr;
    ec = iShare->Attach(MemoryProtection_Read, &addr);
    if (FAILED(ec)) {
        printf("Attach shared memory failed, ec = 0x%08x.\n", ec);
        iShare->Release();
        return -1;
    }

    // get data from shared memory
    Int32 nMagic = *(Int32 *)addr;
    printf("Get data %d from shared memory.\n", nMagic);

    ec = iShare->Detach();
    if (FAILED(ec)) {
        printf("Detach shared memory failed, ec = 0x%08x.\n", ec);
    }

    iShare->Release();

    return 0;
}



//==========================================================================
// Output:
//
//  Get shared memory failed, ec = 0x810c0000.
//
//==========================================================================

