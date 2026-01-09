/*In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs.*/

#include <stdio.h>

void reverse(char s[]){
    int start=0;
    int len;
    
    for (len = 0; s[len] != '\0'; len++);
    len--;
    while(start<len){
        char temp=s[start];
        s[start]=s[len];
        s[len]=temp;
        start++;
        len--;
    }
}

void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;

    do {
        int digit = n % 10;
        if (digit < 0)
            digit = -digit;

        s[i++] = digit + '0';
        n /= 10;
    } while (n != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[50];

    itoa(-2147483648, s);
    printf("%s\n", s);

    return 0;
}
