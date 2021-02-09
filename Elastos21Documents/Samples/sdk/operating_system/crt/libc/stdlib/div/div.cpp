//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _getch.cpp: This example takes two integers as command-line
 * arguments and displays the results of the integer
 * division. This program accepts two arguments on the
 * command line following the program name, then calls
 * div to divide the first argument by the second.
 * Finally, it prints the structure members quot and rem.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int x,y;
    div_t div_result;

    x = 876;
    y = 13;

    printf("x is %d, y is %d\n", x, y);
    div_result = div(x, y);
    printf("The quotient is %d, and the remainder is %d\n",
              div_result.quot, div_result.rem);

    return 0;
}


/*
Output

    x is 876, y is 13
    The quotient is 67, and the remainder is 5
*/
