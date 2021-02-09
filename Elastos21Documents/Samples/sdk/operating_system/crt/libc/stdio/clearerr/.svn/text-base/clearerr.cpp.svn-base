//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* clearerr.cpp: This program creates an error
 * on the standard input stream, then clears
 * it so that future reads won't fail.
 */

#include <stdio.h>

int main( void )
{
   int c;
   /* Create an error by writing to standard input. */
   putc( 'c', stdin );
   if( ferror( stdin ) )
   {
      printf( "Write error\n" );
      clearerr( stdin );
   }

   /* See if read causes an error. */
   printf( "Will input cause an error? " );
   c = getc( stdin );
   if( ferror( stdin ) )
   {
      printf( "Read error" );
      clearerr( stdin );
   }

   return 0;
}


/*
Output

    Write error: No error
    Will input cause an error? n
*/


