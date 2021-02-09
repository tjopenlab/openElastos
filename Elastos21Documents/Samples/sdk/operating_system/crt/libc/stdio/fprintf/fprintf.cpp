//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fprintf.cpp: This program uses fprintf to format various
 * data and print it to the file named FPRINTF.OUT. It
 * then displays FPRINTF.OUT on the screen using the system
 * function to invoke the operating-system TYPE command.
 */

#include <stdio.h>
#include <stdlib.h>

FILE *stream;

int main()
{
    int     i = 10;
    double fp = 1.5;
    char    s[] = "this is a string";
    char    c = '\n';
    char buffer[100];

    if ((stream = fopen("fprintf.out", "w")) == NULL)
        printf("problem open the file!");
    else {
        fprintf(stream, "%s%c", s, c);
        fprintf(stream, "%d\n", i);
        fprintf(stream, "%f\n", fp);
        fclose(stream);
    }
    if ((stream = fopen("fprintf.out", "r")) != NULL) {
        if (fread(buffer, sizeof(char),100, stream) == NULL)
            printf("fread error\n");
        else {
            printf("input is :\n");
            printf("%s\n", buffer);
        }
        fclose(stream);
    }
    else
        printf("problem open the file!\n");

    return 0;
}

/*
Output to the 'fprintf.out'
    input is :
    this is a string
    10
    1.500000
*/
