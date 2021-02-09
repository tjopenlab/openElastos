//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>

_ELASTOS_NAMESPACE_USING

EXTERN_C int __stdcall _SysSetHook(int hHook, const void *pHookProc);

void hooktest(int id, int nCode, void *pParam)
{
    printf("hooktest %d\n", id);
}

EXTERN_C Boolean __stdcall DllMain(
                PVoid hDllHandle, UInt32 dwReason, PVoid preserved)
{
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        _SysSetHook(20, (const void *)hooktest);
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }
    return TRUE;
}
