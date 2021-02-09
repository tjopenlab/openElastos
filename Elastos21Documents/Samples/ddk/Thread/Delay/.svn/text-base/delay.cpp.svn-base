//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description  : This sample demonstrates how to use Yield and Delay.
//
//==========================================================================

#include <ddk.h>

ECode DoMain()
{
    uint_t nDelay = 100;

    //Yield current thread, let some other thread execute
    DzYield();

    //write some datas to some hardware
    //......

    //Delay current thread for nDelay microseconds
    DzDelay(nDelay);

    return NOERROR;
}
