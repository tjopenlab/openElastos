//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* mblen.cpp:this program use mblen to display the length of multibyte
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int     i;
    char    *pmbc = (char *)malloc(sizeof(char));


    i = mblen(pmbc, 0);
    printf("Length in bytes of multibyte character %x: %u\n", pmbc, i);
    free(pmbc);

    pmbc = NULL;
    i = mblen(pmbc, 1);
    printf("Length in bytes of NULL multibyte character %x: %u\n", pmbc, i);

    i = mblen("   aaaa", 1);
    printf("Length in bytes of multibyte character: %u\n", i);

    return 0;

}


/*
Output

    Length in bytes of multibyte character 10540: 0
    Length in bytes of NULL multibyte character 0: 0
    Length in bytes of multibyte character: 1
*/
