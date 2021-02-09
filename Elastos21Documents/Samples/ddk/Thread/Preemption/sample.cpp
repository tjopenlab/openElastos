//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了DisablePreemption和RestorePreemption方法。
//==========================================================================
#include <ddk.h>

ECode DoFunc()
{
    bool_t bSuccess;

    //Disable the system's preemption, to avoid competitions
    //occurring on the shared datas.
    //Save the previous state
    bSuccess = DzDisablePreemption();

    //Now can use the shared datas exclusively
    //......

    //Restore the system's preemption to previous state
    DzRestorePreemption(bSuccess);

    return NOERROR;
}
