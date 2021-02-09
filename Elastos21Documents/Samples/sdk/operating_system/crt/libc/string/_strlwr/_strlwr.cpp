//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//_strlwr.cpp: This program uses _strlwr to create
//lowercase copies of a mixed-case string.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char string[100] = "The String to End All Strings!";
    char *copy1;
    copy1 = _strlwr(_strdup(string));
    printf("Mixed: %s\n", string);
    printf("Lower: %s\n", copy1);
    free(copy1);
    return 0;
}


//==========================================================================
//Output
//
//    Mixed: The String to End All Strings!
//    Lower: the string to end all strings!
//==========================================================================

