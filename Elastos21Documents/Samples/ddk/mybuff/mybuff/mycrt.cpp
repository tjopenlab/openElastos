//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include "mybuff0.h"
#include "mybuff1.h"

EXTERN IDriver* CDECL CreateMyBuff(uint_t uDeviceNo, void *pvParameter)
{
    ECode ec;

    if (0 == uDeviceNo)
    {
        ec = g_myBuff0.Init();
        if (FAILED(ec))
            return NULL;
        return &g_myBuff0;
    }
    else if(1 == uDeviceNo) {
        return CreateMyBuff1();
    }
    else
        return NULL;
}
