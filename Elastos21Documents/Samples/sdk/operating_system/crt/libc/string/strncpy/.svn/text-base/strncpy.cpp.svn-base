//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strncpy.cpp:this program copies the initial count characters of strSource to strDest and returns strDest
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char string[100] = "Cats are nice usually";
    printf ("Before: %s\n", string);
    strncpy(string, "Dogs", 4);
    strncpy(string + 9, "mean", 4);
    printf ("After:  %s\n", string);

    return 0;
}

//==========================================================================
//Output
//
//    Before: Cats are nice usually
//    After:  Dogs are mean usually
//==========================================================================
