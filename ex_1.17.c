#include<stdio.h>

#define MAX 1000

int my_getline(char s[], int lim)
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 1)
            s[i] = c;
        ++i;
    }

    if (c == '\n') {
        if (i < lim - 1)
            s[i] = c;
        ++i;
    }

    if (i < lim)
        s[i] = '\0';
    else
        s[lim - 1] = '\0';

    return i;
}

int main(){
    int c;
    int len=0;
    char line[MAX];
    int a=0;

    while((len=my_getline(line,MAX))>0){
        if (len>80){
            ++a;
            printf("%s",line);
        }

    }
    printf("number of lines of length above 80 : %d",a);
}