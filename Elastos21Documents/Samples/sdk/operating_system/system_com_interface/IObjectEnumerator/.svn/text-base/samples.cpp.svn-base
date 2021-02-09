//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates the using of the
//               IObjectEnumerator.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess *iProc;

    // Gets the current process
    iProc = CProcess::GetCurrent();

    // Gets the module enumerator
    IObjectEnumerator   *iMods;
    ec = iProc->GetAllModules ((IObjectEnumerator **)&iMods);
    if (FAILED(ec)) {
        printf("Get module enumerator failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // Resets the enumerator to the initial state
    ec = iMods->Reset();
    if (FAILED(ec)) {
        printf("Process enumerator Reset failed, ec = 0x%08x.\n", ec);
        iMods->Release();
        return -1;
    }

    printf("All modules in the process:\n");
    // enum the moudle
    // Advances the pointer of object enumerator to the next object
    Boolean bSucceeded;
    ec = iMods->MoveNext(&bSucceeded);
    while (SUCCEEDED(ec) && bSucceeded) {
        IModule  *iMod;
        // Gets the current object of the enumerator
        ec = iMods->Current((IInterface**)&iMod);
        if (FAILED(ec)) {
            printf("Enumerate current module failed, ec = 0x%08x.\n", ec);
            iMods->Release();
            return -1;
        }

        WStringBuf_<200> ewsbName;
        //Gets the name of the module
        ec = iMod->GetName(&ewsbName);
        if (FAILED(ec)) {
            printf("Get module name failed, ec = 0x%08x.\n", ec);

            iMods->Release();
            iMod->Release();
            return -1;
        }
        printf("    Module Name : %12S\n", (wchar_t*)ewsbName);

        iMod->Release();
        ec = iMods->MoveNext(&bSucceeded);
    }

    iMods->Release();

    return 0;
}

//==========================================================================
// Output:
//
//  All modules in the process:
//      Module Name :  objEnum.exe
//      Module Name :   elacrt.dll
//      Module Name :  elastos.dll
//==========================================================================
