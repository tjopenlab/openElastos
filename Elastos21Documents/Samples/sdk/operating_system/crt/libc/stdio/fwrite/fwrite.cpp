//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fwrite.cpp: This program uses fwrite to write a string to a file.
 */

#include <io.h>
#include <stdio.h>
#include <fcntl.h>


int main()
{
    FILE *stream;
    char list[30] = "this is a test";
    int  numwritten;


    if ((stream = fopen("fwrite.out", "wt")) != NULL) {
        numwritten = fwrite(list, sizeof(char), 25, stream);
        printf("Wrote %d items\n", numwritten);
        fclose(stream);
    }
    else {
        printf("Problem opening the file\n");
        return 1;
    }

    return 0;

}

/*
Output

     Wrote 25 items
*/
