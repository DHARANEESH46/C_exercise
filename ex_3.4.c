#include <stdio.h>

void reverse(char s[]){
    int len=0;
    int start=0;

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
