#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("Longest line length: %d\n", max);
        printf("%s", longest);
    }

    return 0;
}

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

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
