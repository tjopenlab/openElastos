//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* abort.cpp:  This program tries to aborts  the process.
 */

#include  <stdio.h>
#include  <stdlib.h>

int main( void )
{
   FILE *stream;

   if( (stream = fopen( "NOSUCHF.ILE", "r" )) == NULL )
   {
      perror( "Couldn't open file" );
      abort();
   }
   else
      fclose( stream );

    return 0;
}



/*
Output

    Couldn't open file.No such file or directory
    abnormal program termination
*/
