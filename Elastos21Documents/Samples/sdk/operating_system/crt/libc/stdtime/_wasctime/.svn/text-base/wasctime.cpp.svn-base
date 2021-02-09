//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* wasctime.cpp: This program places the system time
 * in the long integer aclock, translates it into the
 * structure newtime and then converts it to string
 * form for output, using the asctime function.
 */

#include <time.h>
#include <stdio.h>

struct tm *newtime;
time_t aclock;

int main()
{
    time_t timer;
    static struct tm *timeptr;
    wchar_t *string;

    time(&timer);
    timeptr = localtime(&timer);
    string = _wasctime(timeptr);

    wprintf(L"The current date and time are: %s", string);

    return 0;
}


/*
Output

     The current date and time are: Sun May 01 20:27:01 1994
*/
