//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* iscsymf.cpp: This program uses iscsym to verify c
 * whether it is an english character or UnderLine Character.
 */

#include <stdio.h>
#include <ctype.h>

int main()

   {
    int c = 'a';
    if(iscsymf(c))
        printf("%c is an English character or UnderLine Character! \n",c);
    else
        printf("%c is not an English character and UnderLine Character!\n",c);
    
    c = '_';
    if(iscsymf(c))
        printf("%c is an English character or UnderLine Character! \n",c);
    else
        printf("%c is not an English character and UnderLine Character!\n",c);

    c = '1';
    if(iscsymf(c))
        printf("%c is an English character or UnderLine Character!\n",c);
    else
        printf("%c is not an English character and UnderLine Character!\n",c);

    c = '?';
    if(iscsymf(c))
        printf("%c is an English character or UnderLine Character!\n",c);
    else
        printf("%c is not an English character and UnderLine Character!\n",c);
        
    return 0;

}



/*
Output

      a is an English character or UnderLine Character!
      _ is an English character or UnderLine Character!
      1 is not an English character and UnderLine Character!
      ? is not an English character and UnderLine Character!
*/
