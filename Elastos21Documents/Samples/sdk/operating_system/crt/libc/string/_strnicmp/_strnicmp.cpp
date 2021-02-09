//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// strnicmp.cpp:this program compares, at most, the first count characters of string1 and string2


#include <string.h>
#include <stdio.h>

char string1[] = "The quick brown dog jumps over the lazy fox";
char string2[] = "The QUICK brown fox jumps over the lazy dog";

int main()
{
    char tmp[20];
     int result;
     printf("Compare strings:\n\t\t%s\n\t\t%s\n\n", string1, string2);

     printf("Function:\tstrnicmp _strnicmp (first 10 characters only)\n");
     result = _strnicmp(string1, string2, 10);
     if (result > 0)
         strcpy(tmp, "greater than");
     else if (result < 0)
         strcpy(tmp, "less than");
     else
         strcpy(tmp, "equal to");
     printf("Result:\t\tString 1 is %s string 2\n\n", tmp);

     return 0;
}

//==========================================================================
//Output
//
//    Compare strings:
//                    The quick brown dog jumps over the lazy fox
//                    The QUICK brown fox jumps over the lazy dog
//
//    Function:       strnicmp _strnicmp (first 10 characters only)
//    Result:         String 1 is equal to string 2
//==========================================================================
