//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fputc.cpp: This program uses fputc
 * to send a character array to stdout.
 */

#include <stdio.h>

int main()
{
   char strptr1[] = "This is a test of fputc!!\n";
   char *p;

   /* Print line to stream using fputc. */
   p = strptr1;
   while ((*p != '\0') && fputc(*(p++), stdout) != EOF) ;

   return 0;
}


/*
Output

    This is a test of fputc!!
*/
