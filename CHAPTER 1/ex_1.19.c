/*Write a function reverse(s) that reverses the character string s. Use it to
write a program that reverses its input a line at a time.*/

#include <stdio.h>

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
void reverse(char s[],int lim){
    lim--;
    int start=0;
    while(start<lim){
        char temp=s[start];
        s[start]=s[lim];
        s[lim]=temp;
        start++;
        lim--;
    }
    printf("%s\n",s);
}

int main(){
    int c;
    int len=0;
    char line[MAX];

    while((len=my_getline(line,MAX))>0){
        reverse(line,len);
    }
}