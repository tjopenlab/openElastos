//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================



#include <stdio.h>
#include <time.h>
#include <math.h>



int main()
{
    tm   tmDate   =   {0};
    tmDate.tm_mday=31;
    tmDate.tm_mon=1;
    tmDate.tm_year=106;
    time_t   m_time=mktime(&tmDate);

    printf("%d",tmDate.tm_year) ;
    printf("%d",tmDate.tm_mon) ;
    return 0;
}

//==========================================================================
//Output
//
//    1061
//==========================================================================
