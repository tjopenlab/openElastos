//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strlen.cpp:this program use strlength to get the length of string
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char buffer[61] = "How long am I?";
    int  len;
    len = strlen(buffer);
    printf("'%s' is %d characters long\n", buffer, len);

    return 0;
}

/*
Output

    'How long am I?' is 14 characters long
*/
