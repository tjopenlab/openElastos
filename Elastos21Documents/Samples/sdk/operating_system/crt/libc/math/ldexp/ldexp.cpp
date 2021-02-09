//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ldexp.cpp: This program uses ldexp to Get double-point value from mantissa and exponent. 
 */

#include <math.h>
#include <stdio.h>

int main()
      {
        double x=2.0,result;
        int exp=6;
        
        result=ldexp(x,exp);  // 1.0*2^6
        printf("%.2f^%d=%.2f",x,exp,result);
        
        return 0;
      }




/*
Output

    2.00^6=128.00
*/
