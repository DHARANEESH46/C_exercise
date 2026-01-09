/*Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n)
{
    unsigned int mask;
    unsigned int ybits;

    mask = ~(~0 << n);

    x = x ^ (mask << (p - n + 1));

    return x;
}

int main()
{
    unsigned int x = 15;   
    int p = 2;
    int n = 1;

    unsigned int result = setbits(x, p, n);

    printf("Result = %u\n", result);

    return 0;
}
