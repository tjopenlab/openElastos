//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fseek.cpp: This program opens the file FSEEK.OUT and
 * moves the pointer to the file's beginning.
 */

#include <stdio.h>

int main()
{
    FILE *stream;
    char line[81];
    int  result;

    stream = fopen("fseek.out", "w+");
    if (stream == NULL)
        printf("The file fseek.out was not opened\n");
    else {
        fprintf(stream, "The fseek begins here: "
                              "This is the file 'fseek.out'.\n");
        result = fseek(stream, 23L, SEEK_SET);
        if (result)
            perror("Fseek failed");
        else {
            printf("File pointer is set to middle of first line.\n");
            fgets(line, 80, stream);
            printf("%s", line);

        }
        fclose(stream);
    }

    return 0;
}

/*
Output

     File pointer is set to middle of first line.
     This is the file 'fseek.out'.
*/
