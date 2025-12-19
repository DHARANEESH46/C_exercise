#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int mask;
    unsigned int ybits;

    mask = ~(~0 << n);

    ybits = y & mask;

    x = x & ~(mask << (p - n + 1));

    x = x | (ybits << (p - n + 1));

    return x;
}

int main()
{
    unsigned int x = 204;   
    unsigned int y = 170;  
    int p = 4;
    int n = 3;

    unsigned int result = setbits(x, p, n, y);

    printf("Result = %u\n", result);

    return 0;
}
