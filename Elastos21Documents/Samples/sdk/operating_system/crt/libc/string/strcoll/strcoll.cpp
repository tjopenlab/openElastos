//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//strcoll.cpp:this program use strcoll to returns a value indicating the relationship of string1 to string2
//

#include <string.h>
#include <stdio.h>

char string1[] = "The quick brown dog jumps over the lazy fox";
char string2[] = "The QUICK brown dog jumps over the lazy fox";

int main()
{
    char tmp[20];
    int result;
    /* Case sensitive */
    printf("Compare strings:\n\t%s\n\t%s\n\n", string1, string2);
    result = strcoll(string1, string2);
    if (result > 0)
        strcpy(tmp, "greater than");
    else if (result < 0)
        strcpy(tmp, "less than");
    else
        strcpy(tmp, "equal to");
    printf("\tstrcoll:   String 1 is %s string 2\n", tmp);

    return 0;
}


//==========================================================================
//Output
//
//    Compare strings:
//            The quick brown dog jumps over the lazy fox
//            The QUICK brown dog jumps over the lazy fox
//
//            strcoll:   String 1 is greater than string 2
//==========================================================================
