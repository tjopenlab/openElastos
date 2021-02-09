//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates getting the current
//               process, getting the process id and the start information
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    IProcess * iProc;
    ECode ec;

    // Gets the interface of the current process
    iProc = CProcess::GetCurrent();

    // Gets the process id
    Int32 nProcID = 0;
    ec = iProc->GetId(&nProcID);
    if (FAILED(ec)) {
        printf("Get process id failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("Current Process Id is 0x%x.\n", nProcID);

    // Gets the process start information
    WStringBuf_<200> ewsbName;
    ec = iProc->GetStartInfo(&ewsbName, NULL);
    if (FAILED(ec)) {
        printf("Get processor startinfo failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Current Process Name is \"%S\".\n", (wchar_t*)ewsbName.GetPayload());
    }

    return 0;
}

//==========================================================================
// Output:
//
//  Current Process Id is 0x1fac404.
//  Current Process Name is "procinfo.exe".
//
//==========================================================================
