/*Write a program to print all input lines that are longer than 80 characters.*/

#include<stdio.h>

#define MAX 1000
#define MAXLINES 100

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

int main(void)
{
    char line[MAX];
    char store[MAXLINES][MAX];   
    int len = 0;
    int count = 0;

    while ((len = my_getline(line, MAX)) > 0) {
        if (len > 10) {
            int i = 0;
            while ((store[count][i] = line[i]) != '\0')
                i++;
            count++;
        }
    }

    printf("\nLines longer than 10 characters:\n");
    for (int i = 0; i < count; i++)
        printf("%s", store[i]);

    printf("\nNumber of lines longer than 10: %d\n", count);

    return 0;
}