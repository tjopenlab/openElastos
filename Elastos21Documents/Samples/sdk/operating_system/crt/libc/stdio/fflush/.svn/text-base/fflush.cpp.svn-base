//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fflush.cpp:the program use fflush to check for the buffer was successfully flushed*/
#include <stdio.h>
#include <conio.h>

int main()
{
    int integer;
    int i;
    char string[81];

    /* Read each word as a string. */
    printf("Enter a sentence of four words with scanf: ");
    for (integer = 0; integer < 4; integer++) {
        scanf("%s", string);
        printf("%s\n", string);
    }

    /* You must flush the input buffer before using gets. */
    i = fflush(stdin);
    printf("the return value is : %d\n",i);
    printf("the string is: ");
    printf("%s\n", string);

    return 0;
}

/*
Output

     Enter a sentence of four words with scanf: This is a test
     This
     is
     a
     test
     the return value is : 0
     the string is : test
*/
