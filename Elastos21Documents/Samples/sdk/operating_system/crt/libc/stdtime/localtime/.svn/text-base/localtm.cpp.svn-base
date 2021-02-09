//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* localtm.cpp: This program uses time to get the current time
 * and then uses localtime to convert this time to a structure
 * representing the local time. The program converts the result
 * from a 24-hour clock to a 12-hour clock and determines the
 * proper extension (AM or PM).
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
    struct tm *ptime;
    time_t long_time;

    time(&long_time);                /* Get time as long integer. */
    ptime = localtime(&long_time); /* Convert to local time. */

    printf("The long_time:       %d\n", long_time);
    printf("Current Date :       %d-%d-%d\n",
        ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday);
    printf("Current time :       %d-%d-%d\n",
        ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
    printf("Current weekday :    %d\n", ptime->tm_wday);
    printf("Current year_day :   %d\n", ptime->tm_yday);

    return 0;
}


/*
Output

    The long_time:    1179307373
    Current Date :    2007-5-16
    Current time :    17-22-53
    Current weekday : 3
    Current year_day :135
*/
