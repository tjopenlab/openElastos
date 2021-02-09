//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description  : The following example demonstrates how to use function
//                CSystem::GetAllProcesses to enumerate the processes of current system .
//                It also demonstrates how to use function CProcess::Exit to
//                exit from current process.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IObjectEnumerator *iProcs;

    // get all enumerator of all processes
    ec = CSystem::GetAllProcesses(&iProcs);

    if (FAILED(ec)) {
        printf("get process enumerator failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // Reset
    ec = iProcs->Reset();
    if (FAILED(ec)) {
        printf("reset process enumerator failed, ec = 0x%08x.\n", ec);
        iProcs->Release();
        return -1;
    }

    // enumerate the process
    printf("All Processes in the system :\n");
    printf("Process ID\t\tProcess Name\n");

    Boolean bSucceeded;
    ec = iProcs->MoveNext(&bSucceeded);
    while (ec == 0 && bSucceeded) {
        IProcess * iProc;
        ec = iProcs->Current((IInterface**)&iProc);
        if (FAILED(ec)) {
            printf("enumerate current process failed, ec = 0x%08x.\n", ec);
            iProcs->Release();
            return -1;
        }

        // get process id
        Int32 nID;
        ec = iProc->GetId(&nID);
        if (FAILED(ec)) {
            printf("get process id failed, ec = 0x%08x.\n", ec);
            iProcs->Release();
            iProc->Release();
            return -1;
        }
        printf("%d\t\t", nID);

        // get process name
        WStringBuf_<200> wsName;
        ec = iProc->GetStartInfo(&wsName, NULL);
        if (FAILED(ec)) {
            printf("get process name failed, ec = 0x%08x.\n", ec);
            iProcs->Release();
            iProc->Release();
            return -1;
        }
        printf("%S\n", (wchar_t *)wsName);

       iProc->Release();
        ec = iProcs->MoveNext(&bSucceeded);
    }

    iProcs->Release();

    // will not execute here.
    return 0;
}

//==========================================================================
// Output:
//
//  All Processes in the system :
//  Process ID              Process Name
//  33264644                ezregsvr.exe
//  33265668                elacmd.exe
//  33266692                ezProcess.exe
//
//==========================================================================
