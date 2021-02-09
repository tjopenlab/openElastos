//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _getw.cpp: This program uses _getw to read a word
 * from a stream, then performs an error check.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *stream;
    int i;

    if ((stream = fopen("_getw.exe", "rb")) == NULL)
        printf("Couldn't open file\n");
    else {
        /* Read a word from the stream: */
        i = _getw(stream);

        /* If there is an error... */
        if (ferror(stream)) {
            printf("_getw failed\n");
            clearerr(stream);
        }
        else
            printf("First data word in file: 0x%.4x\n", i);
        fclose(stream);
    }

    return 0;
}


/*
Output

     First data word in file: 0x905a4d
*/
