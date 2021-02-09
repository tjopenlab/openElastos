//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates getting the all modulers
//               in the process.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess * iProc;

    // get current process interface
    iProc = CProcess::GetCurrent();

    // get module enumerator
    IObjectEnumerator * iMods;
    ec = iProc->GetAllModules((IObjectEnumerator **)&iMods);
    if (FAILED(ec)) {
        printf("Get module enumerator failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // Reset
    ec = iMods->Reset();
    if (FAILED(ec)) {
        printf("Reset module enumerator failed, ec = 0x%08x.\n", ec);
        iMods->Release();
        return -1;
    }

    // enumerate the process
    printf("All modules in the process : \n");

    Boolean bSucceeded;
    ec = iMods->MoveNext(&bSucceeded);
    while (SUCCEEDED(ec) && bSucceeded) {
        IModule *iMod;
        ec = iMods->Current((IInterface**)&iMod);
        if (FAILED(ec)) {
            printf("Enumerator current process failed. ec = 0x%08x.\n", ec);
            iMods->Release();
            return -1;
        }

        // get moduler name
        WStringBuf_<256> ewsbName;
        ec = iMod->GetName(&ewsbName);
        if (FAILED(ec)) {
            printf("Get module name failed, ec = 0x%08x.\n", ec);
            iMods->Release();
            iMod->Release();
            return -1;
        }
        printf("Process Name : %S\n", (wchar_t*)ewsbName);

        iMod->Release();

        ec = iMods->MoveNext(&bSucceeded);
    }

    iMods->Release();

    return 0;
}

//==========================================================================
// Output:
//
//  All modules in the process :
//  Process Name : proModules.exe
//  Process Name : elacrt.dll
//  Process Name : elastos.dll
//
//==========================================================================
