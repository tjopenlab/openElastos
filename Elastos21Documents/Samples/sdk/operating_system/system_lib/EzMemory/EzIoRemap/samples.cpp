//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//========================================================================
// Description  : The following example shows how to use the API
//                CVirtualMemory::IoRemap
//========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

//==============================================================
// Description  : Error Handler
//==============================================================

//描述：本测试用例首先调用CVirtualMemory::IoRemap将指定的IO地址段映射到进程虚存段上。如果映射过程出错就打印出错信息并返回。

void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}


int main(int argn, char** argv)
{
    Address IoAddr = 0x000B8000;
    UInt32 uSize = 4096;
    ECode ec;
    Address addr;

    printf("Call CVirtualMemory::IoRemap to map IO Address 0x%08x...\n", IoAddr);

    ec = CVirtualMemory::IoRemap(0, uSize, IoAddr, 0, MemoryProtection_Read, &addr);
    if (FAILED(ec)) {
        HandleError("CVirtualMemory::IoRemap failed.", ec);
        return 1;
    }

    printf("Call CVirtualMemory::Free...\n");
    CVirtualMemory::Free(addr, uSize);

    return 0;

}

