//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// strcspn.cpp:this program returns the index of the first occurrence of a character in string
//               that belongs to the set of characters in strCharSet
//

#include <string.h>
#include <stdio.h>

int main()
{
    char string[] = "xyzabc";
    int  pos;

    pos = strcspn(string, "abc");
    printf("First a, b or c in %s is at character %d\n",
              string, pos);
    return 0;
}

//==========================================================================
//Output
//
//    First a, b or c in xyzabc is at character 3
//==========================================================================
