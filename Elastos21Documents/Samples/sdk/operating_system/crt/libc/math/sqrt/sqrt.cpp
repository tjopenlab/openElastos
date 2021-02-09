//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* sqrt.cpp: This program calculates a square root. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    double question = 45.35, answer;

    answer = sqrt(question);
    if (question < 0)
        printf("Error: sqrt returns %.2f\n, answer");
    else
        printf("The square root of %.2f is %.2f\n", question, answer);

    return 0;
}

/*
Output

     The square root of 45.35 is 6.73
*/
