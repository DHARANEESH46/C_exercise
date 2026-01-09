/*Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.*/

#include <stdio.h>
#include <stdio.h>

void itoa_recursive(int n, char s[])
{
    static int i = 0;
    int digit;

    if (n < 0 && i==0) {
        s[i++] = '-';
    }

    digit = n % 10;
    if (digit < 0)
        digit = -digit;

    if (n / 10)
        itoa_recursive(n / 10, s);

    s[i++] = digit + '0';
    s[i] = '\0';
}


int main()
{
    char s[50];

    itoa_recursive(-2147483648, s);
    printf("%s\n", s);

    return 0;
}
