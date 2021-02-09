//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void SampleFunc()
{
    SystemTime etTime;

    // Gets the system time.
    DzGetSystemTime(&etTime);

    // Sets the system time.
    DzSetSystemTime(etTime);
}
