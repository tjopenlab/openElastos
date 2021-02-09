//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* getopt.cpp: This program uses getopt to analyse the command line, and check
 * these option.
 */

#include <stdio.h>
#include <getopt.h>

struct_opt opt_data = {1, 1, 0, NULL, NULL};
int main(int argc, char* argv[])
{
    int c, num = 1;
    if (argc < 2) {
        printf("Usage %s output-file\n", argv[0]);
        return 1;
    }

    while ((c = getopt(argc, argv, "a:bcd:", &opt_data)) != END_OF_PARA) {
        switch (c) {
            case 'a':
                printf("the input option %d is %c !\n", num++, c);
                break;
            case 'b':
                printf("the input option %d is %c !\n", num++, c);
                break;
            case 'c':
                printf("the input option %d is %c !\n", num++, c);
                break;
            case 'd':
                printf("the input option %d is %c !\n", num++, c);
                break;
            case '?':
                printf("the input option %d is wrong!\n", num++);
                printf("error: %s\n", opt_data.pErr);
                break;
            default:
                printf("error!\n");
                break;
        }
        if (opt_data.optarg) {
            printf("the argument is %s.\n", opt_data.optarg);
            opt_data.optarg = NULL;
        }
    }
    printf("%s \n", "getopt testing is over!");

    return 0;
}


/* getopt -a 123 -b c */
/*
Output

    the input option 1 is a !
    the argument is 123.
    the input option 2 is b !
    getopt testing is over!
*/
