//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* bsearch.cpp: This program reads the command-line
 * parameters, sorting them with qsort, and then
 * uses bsearch to find the word "cat."
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int __cdecl compare(const void *arg1, const void *arg2)
{
    /* Compare all of both strings: */
    return _stricmp(*(char **)arg1, *(char **)arg2);
}

int main(int argc, char **argv)
{
    char **result;
    char *key = "cat";
    int i;

    /* Sort using Quicksort algorithm: */

    qsort((void *)argv, (size_t)argc, sizeof(char *), compare);

    for (i = 1; i < argc; ++i)     /* Output sorted list */
        printf("%s ", argv[i]);


    /* Find the word "cat" using a binary search algorithm: */
    result = (char **)bsearch((char *) &key, (char *)(argv + 1), argc - 1,
            sizeof(char *), compare);

    if (result)
        printf("\n%s found at %X\n", *result, result);
    else
        printf("\nCat not found!\n");

    return 0;
}

/*
Input
    [/$] bsearch dog pig horse cat human rat cow goat

Output
    cat cow dog goat horse human pig rat
    cat found at 1FFFFDA0
*/
