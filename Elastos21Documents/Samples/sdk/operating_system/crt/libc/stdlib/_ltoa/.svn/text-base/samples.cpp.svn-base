//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// discription:This program converts long of various
// sizes to strings in various radixes.
//==========================================================================

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buffer[40];
    long l = -344115L;

    _ltoa(l, buffer, 2);
    printf("String of long int %ld (radix 2): %s\n", l, buffer);

    _ltoa(l, buffer, 10);
    printf("String of long int %ld (radix 10): %s\n", l, buffer);

    _ltoa(l, buffer, 16);
    printf("String of long int %ld (radix 16): 0x%s\n", l, buffer);

    return 0;
}


//==========================================================================
//Output
//
//    String of long int -344115 (radix 2): 11111111111110101011111111001101
//    String of long int -344115 (radix 10): -344115
//    String of long int -344115 (radix 16): 0xfffabfcd
//==========================================================================
