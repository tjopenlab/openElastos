//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _itoa.cpp: This program converts integers of various
 * sizes to strings in various radixes.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buffer[20];
    int  i = 3445;
    long l = -344115L;
    unsigned long ul = 1234567890UL;

    _itoa(i, buffer, 10);
    printf("String of integer %d (radix 10): %s\n", i, buffer);
    _itoa(i, buffer, 16);
    printf("String of integer %d (radix 16): 0x%s\n", i, buffer);
    _itoa(i, buffer, 2 );
    printf("String of integer %d (radix 2): %s\n", i, buffer);

    _ltoa(l, buffer, 16);
    printf("String of long int %ld (radix 16): 0x%s\n", l,
                                                                     buffer);

    _ultoa(ul, buffer, 16);
    printf("String of unsigned long %lu (radix 16): 0x%s\n", ul,
                                                                     buffer);

    return 0;
}


/*
Output

    String of integer 3445 (radix 10): 3445
    String of integer 3445 (radix 16): 0xd75
    String of integer 3445 (radix 2): 110101110101
    String of long int -344115 (radix 16): 0xfffabfcd
    String of unsigned long 1234567890 (radix 16): 0x499602d2
*/
