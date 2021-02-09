//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description: The following example demonstrates getting the address of
//              the resource section
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode  ec;

    // Loads a module that has resource section.
    IModule *iModule;
    ec = CModule::Load(L"elacrt.dll", 0, &iModule);
    if (FAILED(ec)) {
        printf("Load module elacrt.dll failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("Load module elacrt.dll successfully.\n");

    //Gets the address of the resource section
    Address addr;
    ec = iModule->GetResourceSection(&addr);
    if (FAILED(ec)) {
        printf("Get resource section address failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("The address of the resource section is 0x%08x.\n", addr);
    }

    iModule->Release();

    return 0;
}

//==========================================================================
// Output:
//
//  Load module elacrt.dll successfully.
//  Get resource section address failed, ec =0x810c0000..
//
//==========================================================================
