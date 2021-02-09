//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// discription: This program prompts the user for a yes or no and returns
// an exit code of 1 if the user answers Y or y; otherwise it returns 0.
// The error code could be tested in a batch file.
//==========================================================================

#include <stdlib.h>
#include <stdio.h>


int main()
{
    int ch;

    printf("Yes or no? ");
    ch = getwchar();
    printf("\n");
    if (ch == 'Y' || ch == 'y')
        exit(1);
    else
        exit(0);
    return 0;
}


//==========================================================================
//Output:
//  Yes or no? Y
//==========================================================================
