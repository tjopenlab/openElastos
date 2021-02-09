//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* frexp.cpp: This program uses frexp to breaks a double-point number into a normalized fraction and an integral power of 2. It stores the integer exponent in the int object pointed to by exp.
.
 */

#include <math.h>
#include <stdio.h>

int main()
      {
        double x;
        int expptr;
        
        x=frexp(64.0,&expptr);
        printf("64.0=%.2f*2^%d",x,expptr);
        
        return 0;
      }



/*
Output

    64.0=0.50*2^7
*/
