#include<stdio.h>
#define lim 5

int main(){
    int i = 0;
    int c;
    char s[lim];

    while (1) {
        if (i >= lim - 1)       
            break;

        c = getchar();         
        if (c == '\n')         
            break;
        if (c == EOF)         
            break;

        s[i] = c;
        i++;
}
}

