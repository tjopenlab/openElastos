//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates various module activities
//               * get the address of the function by name
//               * get the address of the function by ordinal
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

//
// Description  : Module Name
//
#define MODULE_NAME     L"elacrt.dll"

//
// Description  : Function Name
//
#define FUNCTION_NAME   "printf"

//
// Description  : Functin Ordinal
//
#define FUNCTION_ORDINAL 1

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

    // Gets the address of the function by name.
    Address  addr;
    ec = iModule->GetProcAddressByName(FUNCTION_NAME, &addr);
    if (SUCCEEDED(ec)) {
        printf("Get function address by name[%s]: 0x%08x.\n",
            FUNCTION_NAME, addr);
    }
    else {
        printf("Get function address by name[%s] failed, ec = 0x%08x.\n",
            FUNCTION_NAME, ec);
    }

    // Gets the address of the function by ordinal.
    ec = iModule->GetProcAddressByOrdinal(FUNCTION_ORDINAL, &addr);
    if (SUCCEEDED(ec)) {
        printf("Get function address by ordinal[%d]: ec = 0x%08x.\n",
            FUNCTION_ORDINAL, addr);
    }
    else {
        printf("Get function address by ordinal[%d] failed, ec = 0x%08x.\n",
            FUNCTION_ORDINAL, ec);
    }

    // Releases the module object.
    iModule->Release();

    return 0;
}

//==========================================================================
// Output:
//
// Get function address by name[printf]: 0x3fbe5070.
// Get function address by ordinal[1]: ec = 0x3fbd3000.
//
//==========================================================================
