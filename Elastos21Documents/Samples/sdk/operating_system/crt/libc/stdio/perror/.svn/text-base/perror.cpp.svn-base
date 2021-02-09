//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* perror.cpp: This program attempts to open a file which doesn't exist,
 * then attempts to use sqrt to calculates the square root of a negative.
 */

#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp;  //file pointer
    double x = 10;
    double y;
    //f:\file.txt doesn't exist.
    fp = fopen("U:\\file.txt", "w");
    if (fp == NULL) {
        perror("perror says open the file failed");
    }
    else {
        perror("perror says open file no error");
        fclose(fp);
    }
    //the sqrt's argument is minor to zero
    y = sqrt(x);
    perror("The argument of the funtion is out of domian");

    return 0;
}

/*
Output

    perror says open the file failed:No such file of directory
    The argument of the function is out of domian:Domain error
*/
