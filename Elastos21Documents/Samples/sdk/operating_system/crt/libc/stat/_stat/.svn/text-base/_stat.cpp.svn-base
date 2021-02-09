//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _stat.cpp: This program uses the _stat function to
 * report information about the file named _stat.cpp.
 */

#include <time.h>
#include <stat.h>
#include <stdio.h>

int main()
{
    struct stat buf;
    int result;

    /* Get data associated with "stat.c": */
    result = _stat("_stat.exe", &buf);

    /* Check if statistics are valid: */
    if (result != 0)
        perror("Problem getting information");
    else {
        /* Output some of the statistics: */
        printf("File size      : %ld\n", buf.st_size);
        printf("Drive            : %c:\n", buf.st_dev + 'A');
        printf("Time modified : %s\n", ctime(&buf.st_atime));
    }

    return 0;
}


/*
Output

    File size      : 41088
    Drive            :  :
    Time modified : Tue Nov 06 00:00:00 2007
*/
