//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _putw.cpp: This program uses _putw to write a
 * word to a stream, then performs an error check.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *stream;
    unsigned u;
    if ((stream = fopen("data.out", "wb")) == NULL) {
        printf("problem open the file!\n");
        exit(1);
    }
    for (u = 0; u < 10; u++) {
        _putw(u + 0x2130, stdout);
        _putw(u + 0x2130, stream);    /* Write word to stream. */
        if (ferror(stream)) {            /* Make error check. */
            printf("_putw failed");
            clearerr(stream);
            exit(1);
        }
    }
    printf("Wrote ten words\n");
    fclose(stream);

    return 0;
}

/*
Output

     0!  1!  2!  3!  4!  5!  6!  7!  8!  9!  Wrote ten words
*/
