//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <mdrivers.h>

EZAPI notitest(int id, int nCode, void *pParam)
{
    printf("notitest %d\n", nCode);
    return NOERROR;
}

int main()
{
    KPD_DATA key = {100, 0};
    EzNotify(EVENT_KEYPAD, 0, &key);

    EzSetBackLight(5);
    //StartVibration();
    EzAddNotify(10, (const void *)notitest);
    getchar();
    return 0;
}
