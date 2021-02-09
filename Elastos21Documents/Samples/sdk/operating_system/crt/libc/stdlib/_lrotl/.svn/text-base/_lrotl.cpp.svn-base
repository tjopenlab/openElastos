//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _lrotl.cpp:this program rotate val left eight times and then
              rotate val right four times.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    unsigned long val = 0x0fac35791;

    printf("0x%8.8lx rotated left eight times is 0x%8.8lx\n",
                val, _lrotl(val, 8));
    printf("0x%8.8lx rotated right four times is 0x%8.8lx\n",
                val, _lrotr(val, 4));
    return 0;
}



/*
Output

    0xfac35791 rotated left eight times is 0xc35791fa
    0xfac35791 rotated right four times is 0x1fac3579
*/
