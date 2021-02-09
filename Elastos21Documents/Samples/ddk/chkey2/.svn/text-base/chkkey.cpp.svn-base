//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <io.h>

BOOL bAutorStartup = TRUE;
void StartupConfig()
{
    int ret;
    if (bAutorStartup) {
        if (_waccess(L"/start.bat", 0) != 0) {
            ret = _wrename (L"/~start.bat", L"/start.bat");
            if (ret == 0) {
                wprintf(L"rename ~start.bat --> start.bat ok\n");
            }
            else {
                wprintf(L"rename ~start.bat --> start.bat failed\n");
            }
        }
    }
    else {
        if (_waccess(L"/start.bat", 0) == 0) {
            ret = _wrename (L"/start.bat", L"/~start.bat");
            if (ret == 0) {
                wprintf(L"rename start.bat --> ~start.bat ok\n");
            }
            else {
                wprintf(L"rename start.bat --> ~start.bat failed\n");
            }
        }
    }
}

int __cdecl main()
{
    ECode ec;
    IDriver* pIkeyboard = NULL;
    ec = CSystem::FindRunningObject(L"device:keypad0", (IInterface **)&pIkeyboard);
    if (FAILED(ec)) {
        printf("Find IDriver of keypad failed, %p", ec);
        return 0;
    }

    ec = pIkeyboard->Control(5/*CheckIfKeyHold*/, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL );
    if (FAILED(ec)) {
        //nothing key press down
    }
    else {//return success if any key press&hold
        printf("There is some key hold, u can release now ...\n");
        bAutorStartup = FALSE;
    }

    pIkeyboard->Release();

    StartupConfig();

    return 0;
}
