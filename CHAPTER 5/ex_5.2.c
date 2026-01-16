/*Write getfloat, the floating-point analog of getint. What type does
getfloat return as its function value?*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <ctype.h>

int getfloat(double *pn)
{
    int c, sign;
    double power;

    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int next = getch();

        if (!isdigit(next)) {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * (*pn) + (c - '0');

    if (c == '.') {
        c = getch();
        for (power = 1.0; isdigit(c); c = getch()) {
            *pn = 10.0 * (*pn) + (c - '0');
            power *= 10.0;
        }
        *pn /= power;
    }

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}
