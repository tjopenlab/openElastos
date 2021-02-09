//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This Example shows how to use the API
//                CVirtualMemory::CheckProtection and CVirtualMemory::SetProtection.
//                The example firstly calls CVirtualMemory::Alloc
//                to allocate a readonly memory;
//                If the action is unsuccessful, then print
//                the error information and return;
//                If the action is successful, then calls
//                CVirtualMemory::SetProtection to change the virtual memory attribute;
//                after it, calling CVirtualMemory::CheckProtection to check
//                the memory attribute and print it;
//                finally, calling CVirtualMemory::Free to release
//                the allocated memroy.
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
    const UInt32 uSize = 4096;
    Address addr;
    Boolean bIsValid;

    printf("Call CVirtualMemory::Alloc with MemoryProtection_Read...\n");

    //malloc a piece of read_only memory
    ec = CVirtualMemory::Alloc(0, uSize, 0, MemoryProtection_Read, &addr);
    if (FAILED(ec)) {
        HandleError("CVirtualMemory::Alloc failed.", ec);
        return ec;
    }

    printf("Call CVirtualMemory::CheckProtection with MemoryProtection_Read...\n");

    //check if the memory can be read
    ec = CVirtualMemory::CheckProtection(addr, MemoryProtection_Read, &bIsValid);
    if (NOERROR == ec && bIsValid) {
        printf("Memory is readable.\n");
    }
    else if (NOERROR == ec && !bIsValid) {
        printf("Memory is not readable.\n");
    }
    else {
        HandleError("CVirtualMemory::CheckProtection failed.", ec);
    }

    printf("Call CVirtualMemory::CheckProtection with MemoryProtection_Write...\n");

    //check if the memory can be write
    ec = CVirtualMemory::CheckProtection(addr, MemoryProtection_Write, &bIsValid);
    if (NOERROR == ec && bIsValid) {
        printf("Memory is writable.\n");
    }
    else if (NOERROR == ec && !bIsValid) {
        printf("Memory is not writable.\n");
    }
    else {
        HandleError("CVirtualMemory::CheckProtection failed.", ec);
    }

    printf("Call CVirtualMemory::SetProtection with MemoryProtection_RW...\n");

    //change the protect right of the memory to read and write
    ec = CVirtualMemory::SetProtection(addr, uSize, MemoryProtection_RW);
    if (FAILED(ec)) {
        HandleError("CVirtualMemory::SetProtection failed.", ec);
        goto _exit;
    }

    printf("Call CVirtualMemory::CheckProtection with MemoryProtection_Read...\n");

    //check if the memory can be read
    ec = CVirtualMemory::CheckProtection(addr, MemoryProtection_Read, &bIsValid);
    if (NOERROR == ec && bIsValid) {
        printf("Memory is readable.\n");
    }
    else if (NOERROR == ec && !bIsValid) {
        printf("Memory is not readable.\n");
    }
    else {
        HandleError("CVirtualMemory::CheckProtection failed.", ec);
    }

    printf("Call CVirtualMemory::CheckProtection with MemoryProtection_Write...\n");

    //check if the memory can be write
    ec = CVirtualMemory::CheckProtection(addr, MemoryProtection_Write, &bIsValid);
    if (NOERROR == ec && bIsValid) {
        printf("Memory is writable.\n");
    }
    else if (NOERROR == ec && !bIsValid) {
        printf("Memory is not writable.\n");
    }
    else {
        HandleError("CVirtualMemory::CheckProtection failed.", ec);
    }

_exit:
    printf("Call CVirtualMemory::Free...\n");

    //free the memory
    CVirtualMemory::Free(addr, uSize);

    return 0;
}


//==========================================================================

//  OutPut:

//        Call CVirtualMemory::Alloc with MemoryProtection_Read...
//        Call CVirtualMemory::CheckProtection with MemoryProtection_Read...
//        Memory is readable.
//        Call CVirtualMemory::CheckProtection with MemoryProtection_Write...
//        Memory is not writable.
//        Call CVirtualMemory::SetProtection with MemoryProtection_RW...
//        Call CVirtualMemory::CheckProtection with MemoryProtection_Read...
//        Memory is readable.
//        Call CVirtualMemory::CheckProtection with MemoryProtection_Write...
//        Memory is writable.
//        Call CVirtualMemory::Free...

//==========================================================================
