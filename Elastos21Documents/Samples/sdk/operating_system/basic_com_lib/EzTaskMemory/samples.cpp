//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This sample shows
//                how to use CMemoryHeap::Alloc to allocate memory,
//                how to use CMemoryHeap::Free to free memory,
//                how to use CMemoryHeap::Realloc to reallocate the memory.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

int main()
{
    void *pMem1, *pMem2;
    int i;

    // allocate memory
    pMem1 = CMemoryHeap::Alloc(10, FALSE);
    if (!pMem1) {
        printf("Not engough memory\n");
        return 1;
    }
    printf("Use CMemoryHeap::Alloc to allocate memory.\n");
    // access the memory
    *(int *)pMem1 = 255;

    // realloc the memory
    pMem2 = CMemoryHeap::Realloc(pMem1, 20);
    if (!pMem2) {
        printf("Not engough memory\n");
        CMemoryHeap::Free(pMem1);
        return 1;
    }
    pMem1 = pMem2;

    // read memory
    i = *(int *)pMem1;
    printf("Use CMemoryHeap::Realloc to reallocate memory, "
        "and its first address is %d.\n", i);

    // free memory
    CMemoryHeap::Free(pMem1);
    printf("Use CMemoryHeap::Free to free memory which is reallocated by "
        "CMemoryHeap::Realloc.\n");
    return 0;
}

//==========================================================================
//OutPut:
//  Use CMemoryHeap::Alloc to allocate memory.
//  Use CMemoryHeap::Realloc to reallocate memory, and its first address is 255.
//  Use CMemoryHeap::Free to free memory which is reallocated by CMemoryHeap::Realloc.
//==========================================================================
