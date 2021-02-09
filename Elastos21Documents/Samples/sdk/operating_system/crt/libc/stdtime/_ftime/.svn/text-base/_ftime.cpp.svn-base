//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _ftime.cpp: This program uses _ftime to obtain the current
 * time and then stores this time in timebuffer.
 */

#include <stdio.h>
#include <time.h>
#include <timeb.h>

int main()
{
    struct _timeb timebuffer;
    char *timeline;

    _ftime(&timebuffer);
    timeline = ctime(& (timebuffer.time));

    printf("The time is %.19s.%hu %s", timeline,
        timebuffer.millitm, &timeline[20]);

    return 0;
}


/*
Output

     The time is Tue Mar 21 15:26:41.341 1995
*/
