//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* remove.cpp: This program uses remove to delete REMOVE.OBJ. */

#include <stdio.h>

int main()
{
    if (remove("remove.obj") == -1)
        printf("Could not delete 'REMOVE.OBJ'\n");
    else
        printf("Deleted 'REMOVE.OBJ'\n");

    return 0;
}

/*
Output

     Deleted 'REMOVE.OBJ'
*/
