//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates various module activities
//               * get the base address
//               * get the entry point address
//               * get the memory size
//               * get the address of a section
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

//
// Description  : Module Name
//
#define MODULE_NAME     L"elacrt.dll"

//
// Description  : Section Name
//
#define SECTION_NAME    ".text"

Int32 main()
{
    ECode ec;
    IProcess * iProc = NULL;

    // get current process
    iProc = CProcess::GetCurrent();

    IModule* iModule;
    ec = iProc->GetModuleByName(MODULE_NAME, &iModule);
    if (FAILED(ec)) {
        printf("Get module by name failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("%S Module Infomation:\n", (const WChar *)MODULE_NAME);

    // Gets the base address of the module.
    Address  addr;
    ec = iModule->GetBaseAddress(&addr);
    if (FAILED(ec)) {
        printf("Get base address failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Base address : 0x%08x.\n", addr);
    }

    // Gets the entry pointer address of the module.
    ec = iModule->GetEntryPointAddress(&addr);
    if (FAILED(ec)) {
        printf("Get entry point address failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Entry point address : 0x%08x.\n", addr);
    }

    // Gets the size of the module.
    MemorySize uSize;

    ec = iModule->GetMemorySize(&uSize);
    if (FAILED(ec)) {
        printf("Get memory size failed, ec = 0x%08x.\n", ec);
    }
    else {
       printf("Memory size : %dBytes.\n", uSize);
    }

    // Gets the address of the section.
    ec = iModule->GetSectionByName(SECTION_NAME, &addr);
    if (FAILED(ec)) {
        printf("Get TEXT section address failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("TEXT section address : 0x%08x.\n", addr);
    }

    // Releases the module object.
    iModule->Release();

    return 0;
}

//==========================================================================
//Output:
//
//  elacrt.dll Module Infomation:
//  Base address : 0x3fbd2000.
//  Entry point address : 0x3fbee220.
//  Memory size : 331776Bytes.
//  TEXT section address : 0x3fbd3000.
//
//==========================================================================
