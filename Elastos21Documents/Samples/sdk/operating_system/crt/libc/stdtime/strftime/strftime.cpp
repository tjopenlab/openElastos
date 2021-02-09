//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strftime.cpp: this program use strftime to calculate the number of characters placed in today
 */

#include <stdio.h>
#include <time.h>

int main()
{
    char tmpbuf[128];
    struct tm *today;
    time_t ltime;
    time(&ltime);
    today = localtime(&ltime);
    strftime(tmpbuf, 128,
         "Today is %A, day %d of %B in the year %Y.\n", today);
    printf(tmpbuf);

    return 0;
}

/*
Output

    Today is Monday, day 20 of May in the year 2002.
*/
