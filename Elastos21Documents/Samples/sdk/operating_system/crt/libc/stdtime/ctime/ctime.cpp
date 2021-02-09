//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ctime.cpp: This program gets the current
 * time in time_t form, then uses ctime to
 * display the time in string form.
 */

#include <time.h>
#include <stdio.h>

int main()
{
    time_t ltime;

    time(&ltime);
    printf("The time is %s\n", ctime(&ltime));

    return 0;
}


/*
Output

     The time is Fri Apr 29 12:25:12 1994
*/
