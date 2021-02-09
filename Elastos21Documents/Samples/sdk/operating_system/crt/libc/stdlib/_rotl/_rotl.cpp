//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _rotl.cpp: This program uses _rotr and _rotl with
 * different shift values to rotate an integer.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    unsigned val = 0x0fd93;
    printf("0x%4.4x rotated left three times is 0x%4.4x\n",
              val, _rotl(val, 3));
    printf("0x%4.4x rotated right four times is 0x%4.4x\n",
              val, _rotr(val, 4));
    return 0;
}


/*
Output

     0xfd93 rotated left three times is 0x7ec98
     0xfd93 rotated right four times is 0x30000fd9
*/
