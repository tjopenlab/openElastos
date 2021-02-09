//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _alloca.cpp: This program uses _alloca function to
 * allocates memory on the stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NUM 0x80

int main()
{
    int *intArray;

    intArray = (int*)_alloca(sizeof(int) * NUM);
    printf("Integer allocating (number: %d)  OK!\n", sizeof(int) * NUM);

    return 0;
}


/*
Output

    Integer allocating (number: 512)  OK!
*/
