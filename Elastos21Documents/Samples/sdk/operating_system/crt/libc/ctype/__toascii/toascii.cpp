//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* toascii.cpp: This program converts integer 45 and 301
 * into ASCII characters
 */


#include <stdio.h>
#include <ctype.h>

int main()

{
    int c1 = 45, c2 = 301;

    printf("The result c1 is: %d.\n", __toascii(c1));
    printf("The result c2 is: %d.\n", __toascii(c2));

    return 0;
}


/*
Output

    The result c1 is: 45.
    The result c2 is: 45.
*/
