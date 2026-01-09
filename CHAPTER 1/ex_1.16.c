/*Revise the main routine of the longest-line program so it will correctly print
the length of arbitrary long input lines, and as much as possible of the text.*/

#include <stdio.h>

#define MAXLINE 10

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max = 0;
    char line[MAXLINE+1];
    char longest[MAXLINE+1];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("%s", longest);
        printf("Longest line length: %d\n", max);
    }

    return 0;
}

int my_getline(char s[], int lim)       //proper
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim)
            s[i] = c;
        ++i;
    }

    if (c == '\n') {
        if (i < lim)
            s[i] = c;
        ++i;
    }

    if (i < lim)
        s[i] = '\0';
    else
        s[lim] = '\0';

    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
