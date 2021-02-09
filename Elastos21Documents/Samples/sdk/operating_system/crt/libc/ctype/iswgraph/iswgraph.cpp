//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isgraph.cpp: This program uses isprint to verify c
 * whether it is a printable character except blank.
 */

#include <stdio.h>
#include <ctype.h>

int main()
      {
        int c;
        
        c='a';
        printf("%c %s\n",c,isgraph(c)?"is a printable character.":"is not a printable character.");
        c=' ';           // 0x20
        printf("'%c' %s\n",c,isgraph(c)?"is a printable character.":"is not a printable character.");
        c=0x7f;
        printf("%c %s\n",c,isgraph(c)?"is a printable character.":"is not a printable character.");
        
        return 0;
      }


/*
Output

     a  is a printable character.
    ' ' is not a printable character.
    ¡÷ is not a printable character.
*/
