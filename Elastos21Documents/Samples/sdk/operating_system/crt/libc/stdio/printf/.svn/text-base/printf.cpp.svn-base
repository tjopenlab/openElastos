//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* printf.cpp: This program uses the printf and wprintf functions
 * to produce formatted output.
 */

#include <stdio.h>

int main()
{
    char    ch = 'h', *string = "computer";
    int     count = -9234;
    double fp = 251.7366;
    wchar_t wch = L'w', *wstring = L"Unicode";

    /* Display integers. */
    printf("Integer formats:\n"
              "\tDecimal: %d  Justified: %.6d  Unsigned: %u\n",
              count, count, count, count);

    printf("Decimal %d as:\n\tHex: %Xh  C hex: 0x%x  Octal: %o\n",
                count, count, count, count);

    /* Display in different radixes. */
    printf("Digits 10 equal:\n\tHex: %i  Octal: %i  Decimal: %i\n",
                0x10, 010, 10);

    /* Display characters. */

    printf("Characters in field (1):\n%10c%5hc%5C%5lc\n", ch, ch, wch, wch);
    wprintf(L"Characters in field (2):\n%10C%5hc%5c%5lc\n", ch, ch, wch, wch);

    /* Display strings. */

    printf("Strings in field (1):\n%25s\n%25.4hs\n\t%S%25.3ls\n",
    string, string, wstring, wstring);
    wprintf(L"Strings in field (2):\n%25S\n%25.4hs\n\t%s%25.3ls\n",
         string, string, wstring, wstring);

    /* Display real numbers. */
    printf("Real numbers:\n\t%f %.2f %e %E\n", fp, fp, fp, fp);

    /* Display pointer. */
    printf("\nAddress as:\t%p\n", &count);

    /* Count characters printed. */
    printf("\nDisplay to here:\n");
    printf("1234567890123456%n78901234567890\n", &count);
    printf("\tNumber displayed: %d\n\n", count);

    return 0;
}

/*
Output

    Integer formats:
            Decimal: -9234  Justified: -009234  Unsigned: 4294958062
    Decimal -9234 as:
            Hex: FFFFDBEEh  C hex: 0xffffdbee  Octal: 37777755756
    Digits 10 equal:
            Hex: 16  Octal: 8  Decimal: 10
    Characters in field (1):
             h    h    w    w
    Characters in field (2):
             h    h    w    w
    Strings in field (1):
                     computer
                         comp
            Unicode                      Uni
    Strings in field (2):
                     computer
                         comp
            Unicode                      Uni
    Real numbers:
            251.736600 251.74 2.517366e+002 2.517366E+002

    Address as:     0x1ffffd48

    Display to here:
    123456789012345678901234567890
            Number displayed: 16
*/
