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
    char    *pmbhi = "This is a test of _strtowcs.";
    wchar_t pwc[29];

    printf("Convert to wide-character string:%s\n", pmbhi);
    i = _strtowcs(pwc, pmbhi);
    printf("\tCharacters converted: %d\n", i);
    printf("\twide character string: %S\n", pwc);

    return 0;

}


/*
Output

	Convert to wide-character string:This is a test of _strtowcs.
          Characters converted: 28
          wide character string: This is a test of _strtowcs.
*/
