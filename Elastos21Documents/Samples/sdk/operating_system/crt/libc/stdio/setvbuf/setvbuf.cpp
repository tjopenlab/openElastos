//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* setvbuf.cpp: This program opens two streams: stream1
 * and stream2. It then uses setvbuf to give stream1 a
 * user-defined buffer of 1024 bytes and stream2 no buffer.
 */

#include <stdio.h>

int main()
{
    char buf[1024];
    FILE *stream1, *stream2;

    if (((stream1 = fopen("data1", "a")) != NULL) &&
         ((stream2 = fopen("data2", "w")) != NULL)) {
        if (setvbuf(stream1, buf, _IOFBF, sizeof(buf)) != 0)
            printf("Incorrect type or size of buffer for stream1\n");
        else
            printf("'stream1' now has a buffer of 1024 bytes\n");
        if (setvbuf(stream2, NULL, _IONBF, 0) != 0)
            printf("Incorrect type or size of buffer for stream2\n");
        else
            printf("'stream2' now has no buffer\n");
        _fcloseall();
    }
    else
        printf("problem open the file!!");
    return 0;
}


/*
Output

    'stream1' now has a buffer of 1024 bytes
    'stream2' now has no buffer
*/
