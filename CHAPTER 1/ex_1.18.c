/*Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines.*/

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

int trim(char line[],int i)
{
    i--;
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i--;

    if (i < 0) {
        line[0] = '\0';
        return 0;
    }

    line[i + 1] = '\n';
    line[i + 2] = '\0';

    return i + 1;
}


int main()
{
    char line[MAX];
    int len;

    while ((len = my_getline(line, MAX)) > 0) {
        if (trim(line,len) > 0) {
            printf("%s", line);
        }
    }

    return 0;
}
