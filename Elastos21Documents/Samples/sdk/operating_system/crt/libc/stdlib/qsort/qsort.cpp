//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* qsort.cpp: This program reads the command-line
 * parameters and uses qsort to sort them. It
 * then displays the sorted arguments.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int __cdecl compare(const void *arg1, const void *arg2)
{
    /* Compare all of both strings: */
    return _stricmp(* (char**) arg1, * (char**) arg2);
}

int main(int argc, char **argv)
{
    int i;
    /* Eliminate argv[0] from sort: */
    argv++;
    argc--;

    /* Sort remaining args using Quicksort algorithm: */
    qsort((void *)argv, (size_t)argc, sizeof(char *), compare);

    /* Output sorted list: */
    for (i = 0; i < argc; ++i)
        printf("%s ", argv[i]);
    printf("\n");

    return 0;
}

/*
Input
    [/$]qsort every good boy deserves favor

Output

     boy deserves every favor good
*/
