//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* atof.cpp: This program shows how numbers stored
 * as strings can be converted to numeric values
 * using the atof, atoi, and atol functions.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *s; double x; int i; long l;

    s = "  -2309.12E-15";     /* Test of atof */
    x = atof(s);
    printf("atof test: ASCII string: %s\tfloat:  %e\n", s, x);

    s = "7.8912654773d210";  /* Test of atof */
    x = atof(s);
    printf("atof test: ASCII string: %s\tfloat:  %e\n", s, x);

    s = "  -9885 pigs";        /* Test of atoi */
    i = atoi(s);
    printf("atoi test: ASCII string: %s\t\tinteger: %d\n", s, i);

    s = "98854 dollars";      /* Test of atol */
    l = atol(s);
    printf("atol test: ASCII string: %s\t\tlong: %ld\n", s, l);

    return 0;
}


/*
Output

    atof test: ASCII string:   -2309.12E-15 float:  -2.309120e-012
    atof test: ASCII string: 7.8912654773d210       float:  7.891265e+210
    atoi test: ASCII string:   -9885 pigs           integer: -9885
    atol test: ASCII string: 98854 dollars          long: 98854
*/
