//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _mktemp.cpp: The program uses _mktemp to create
 * five unique filenames. It opens each filename
 * to ensure that the next name is unique.
 */

#include <io.h>
#include <string.h>
#include <stdio.h>

char *tempplate = "fnXXXXXX";
char *result;
char names[5][9] = {NULL};

int main()
{
    int i;
    FILE *fp;

    for (i = 0; i < 5; i++) {
        strcpy(names[i], tempplate);
        /* Attempt to find a unique filename: */
        result = _mktemp(names[i]);
        if (result == NULL)
            printf("Problem creating the template");
        else {
            if ((fp = fopen(result, "w")) != NULL)
                printf("Unique filename is %s\n", result);
            else
                printf("Cannot open %s\n", result);
            fclose(fp);
        }
    }

    return 0;
}


/*
Output

    Unique filename is fna13408
    Unique filename is fnb13408
    Unique filename is fnc13408
    Unique filename is fnd13408
    Unique filename is fne13408
*/
