//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* difftime.cpp: This program calculates the amount of time
 * needed to do a floating-point multiply 10 million times.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
     time_t     start, finish;
     long loop;
     double     result, elapsed_time;

     printf("Multiplying 2 floating point numbers 10 million times...\n");

     time(&start);
     for (loop = 0; loop < 10000000; loop++)
          result = 3.63 * 5.27;
     time(&finish);

     elapsed_time = difftime(finish, start);
     printf("\nProgram takes %6.0f seconds.\n", elapsed_time);

     return 0;
}


/*
Output

    Multiplying 2 floating point numbers 10 million times...

    Program takes     36 seconds.
*/
