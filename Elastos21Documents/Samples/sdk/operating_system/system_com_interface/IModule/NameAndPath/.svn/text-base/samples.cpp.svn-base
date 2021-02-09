//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to get the name of the module.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IModule* iModule;

    // Loads the module.
    ec = CModule::Load(L"rsrcdll.dll",0,&iModule);
    if (NOERROR != ec) {
        printf("Load module rsrcdll.dll failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("Load module rsrcdll.dll successfully.\n");

    // Gets the name of the module.
    WStringBuf_<256> ewsbName;
    ec = iModule->GetName(&ewsbName);
    if (FAILED(ec)) {
        printf("Get module name failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Module name is %S.\n", (wchar_t *)ewsbName);
    }

    // Gets the path of the module.
    WStringBuf_<256> ewsbFullPath;
    ec = iModule->GetFullPath(&ewsbFullPath);
    if (FAILED(ec)) {
        printf("Get module full path failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Module full path is %S.\n", (wchar_t *)ewsbFullPath);
    }

    // Releases the module object.
    iModule->Release();
    return 0;
}

//==========================================================================
// Output:
//
//Load module rsrcdll.dll successfully.
//Module name is rsrcdll.dll.
//Module full path is D:/rsrcdll.dll.
//
//==========================================================================
