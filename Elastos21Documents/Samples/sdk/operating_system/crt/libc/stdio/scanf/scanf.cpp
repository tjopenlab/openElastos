//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* scanf.cpp: This program uses the scanf and wscanf functions
  * to read formatted input.
  */

#include <stdio.h>

int main()
{
   int   i, result;
   float fp;
   char  c, s[81];
   wchar_t wc, ws[81];

   printf("\n\nEnter an int, a float, two chars and two strings\n");

   result = scanf("%d %f %c %C %s %S", &i, &fp, &c, &wc, s, ws);
   printf("\nThe number of fields input is %d\n", result);
   printf("The contents are: %d %f %c %C %s %S\n", i, fp, c, wc, s, ws);

   return 0;
}


/*
Output

    
    
    Enter an int, a float, two chars and two strings
    71
    98.6
    h
    z
    Byte characters

    The number of fields input is 6
    The contents are: 71 98.599998 h z Byte characters
*/
