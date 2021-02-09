//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isleadbyte.cpp: This program uses isleadbyte to verify
 * whether the first byte of c is a multibyte character.
 */

#include <stdio.h>
#include <ctype.h>
#include <elastos.h>

int main()
      {
        int c;
        int wc = 0xD6;
        
        c='k';
        {  
        if(isleadbyte(c))
              printf("the first byte of '%c' is a multibyte character\n",c);
        else
              printf("the first byte of '%c' is not a multibyte character\n",c);
        }
        
        c=wc;
        {
        if (isleadbyte(c))  
              printf("the first byte of '%c' is a multibyte character\n",c);
        else
              printf("the first byte of '%c' is not a multibyte character\n",c);
        }
        return 0;
      }


/*
Output

     the first byte of 'k' is not a multibyte character
     the first byte of '0xD6**' is a multibyte character
*/
