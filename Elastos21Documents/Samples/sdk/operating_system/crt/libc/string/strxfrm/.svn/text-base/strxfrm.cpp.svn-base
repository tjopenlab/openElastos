//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strxfrm.cpp:this transforms the string pointed to by strSource into a new collated form that is stored in strDestprogram
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char string[100] = "Cats are nice usually";
    printf("Before: %s\n", string);
    strxfrm(string, "Dogs", 4);
    strxfrm(string + 9, "mean", 4);
    printf("After:  %s\n", string);

    return 0;
}

//==========================================================================
//Output
//
//    Before: Cats are nice usually
//    After:  Dogs are mean usually
//==========================================================================
