//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* mbstowcs.cpp: this program use mbstowcs to convert string to wide-character string
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    char    *pmbhi = "Hi,Elastos!";
    wchar_t pwc[12];

    printf("Convert to wide-character string:%s\n", pmbhi);
    i = mbstowcs(pwc, pmbhi, 12);
    printf("\tCharacters converted: %d\n", i);
    printf("\twide character string: %S\n", pwc);

    return 0;

}


/*
Output

	Convert wide-character string:Hi,Elastos!
	        Characters converted: 11
	        wide character string: Hi,Elastos!
*/
