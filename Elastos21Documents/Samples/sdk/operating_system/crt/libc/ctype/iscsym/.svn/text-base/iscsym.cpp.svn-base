//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* iscsym.cpp: This program uses iscsym to verify c
 * whether it is an english character, UnderLine Character or Number.
 */

#include <stdio.h>
#include <ctype.h>

int main()

   {
    int c = 'a';
    if(iscsym(c))
        printf("%c is an English character, UnderLine Character or Number! \n",c);
    else
        printf("%c is not an English character,  UnderLine Character and Number!\n",c);
    
    c = '_';
    if(iscsym(c))
        printf("%c is an English character, UnderLine Character or Number! \n",c);
    else
        printf("%c is not an English character,  UnderLine Character and Number!\n",c);

    c = '1';
    if(iscsym(c))
        printf("%c is an English character, UnderLine Character or Number! \n",c);
    else
        printf("%c is not an English character,  UnderLine Character and Number!\n",c);

    c = '?';
    if(iscsym(c))
        printf("%c is an English character, UnderLine Character or Number! \n",c);
    else
        printf("%c is not an English character, UnderLine Character and Number!\n",c);
        
    return 0;

}



/*
Output

      a is an English character, UnderLine Character or Number!
      _ is an English character, UnderLine Character or Number!
      1 is an English character, UnderLine Character or Number!
      ? is not an English character,  UnderLine Character and Number!
*/
