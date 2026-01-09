/*Write a program to ``fold'' long input lines into two or more shorter lines after
the last non-blank character that occurs before the n-th column of input. Make sure your
program does something intelligent with very long lines, and if there are no blanks or tabs
before the specified column.*/


#include <stdio.h>

#define MAX 1000
#define n 20


int my_getline(char line[], int limit)
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < limit - 1)
            line[i] = c;
        i++;
    }

    if (c == '\n') {
        if (i < limit - 1)
            line[i] = c;
        i++;
    }

    line[i] = '\0';
    return i;
}

void fold(char s[]){
    int col=0;
    int i=0;

    while(s[i]!='\0'){
        if (col==n){
            putchar('\n');
            if (s[i]==' ' || s[i]=='\t'){
                i++;
            }
            putchar(s[i]);
            col=0;
        }
        else{
            putchar(s[i]);
        }
        col++;
        i++;
    }
}

int main()
{
    char line[MAX];

    while (my_getline(line, MAX) > 0) {
        fold(line);
    }

    return 0;
}
