//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : The following example shows how to use the API
//                CVirtualMemory::Alloc, CVirtualMemory::Commit and CVirtualMemory::Free.
//                The example firstly calls CVirtualMemory::Alloc to
//                allocate an uSize memory block;
//                if the allocation is successful, then write the
//                virtual address to the addr
//                and call CVirtualMemory::Commit to allocate a physical
//                memory meanwhile mapping it
//                to the vitual memory block;finally, calling
//                CVirtualMemory::Free to release the virtual memory block.
//                If the allocation is unsuccessful, then print
//                the error information and return;
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

// Description : printf error information when an error occured
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}


int main()
{
    ECode ec;
    const Int32 uSize = 4096;
    Address addr;

    printf("Call CVirtualMemory::Alloc...\n");

    //malloc a piece of read_only memory
    ec = CVirtualMemory::Alloc(0, uSize, 0, MemoryProtection_Read, &addr);
    if (FAILED(ec)) {
        HandleError("CVirtualMemory::Alloc failed.", ec);
        return ec;
    }

    printf("Call CVirtualMemory::Commit...\n");

    //commit the memory
    ec = CVirtualMemory::Commit(addr);
    if (FAILED(ec)) {
        HandleError("CVirtualMemory::Commit failed.", ec);
    }

    printf("Call CVirtualMemory::Free...\n");

    //free the memory
    CVirtualMemory::Free(addr, uSize);

    return 0;
}


//==========================================================================

//  OutPut:

//        Call CVirtualMemory::Alloc...
//        Call CVirtualMemory::Commit...
//        Call CVirtualMemory::Free...

//==========================================================================
