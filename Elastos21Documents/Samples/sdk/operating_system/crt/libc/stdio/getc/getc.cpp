//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* getc.cpp: This program uses getwc read a line characters from a stream.
 */

#include <stdio.h>

int main()
{
    FILE * fp, *stream;
    char list[50] = "This is a test of Elastos operating system\n";
    int i, number;

    if ((fp = fopen("getwc.txt", "w")) == NULL)
        printf("problem open the file!");
    else {
        number = fwrite(list,sizeof(char), 50, fp);
        fclose(fp);
    }

    if ((stream = fopen("getwc.txt", "r")) == NULL)
        printf("problem open the file!");
    else {
        for (i = 0; i < 50; i++) {
            putwchar(getwc(stream));
        }

        fclose(stream);
    }


    return 0;
}


/*
Output

     This is a test of Elastos operating system
*/
