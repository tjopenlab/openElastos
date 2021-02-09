//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _flushall.C: This program uses _flushall
 * to flush all open buffers.
 */

#include <stdio.h>

int main( void )
{
   int numflushed;

   numflushed = _flushall();
   printf( "There were %d streams flushed\n", numflushed );
   return 0;
}


/*
Output

There were 0 streams flushed
*/
