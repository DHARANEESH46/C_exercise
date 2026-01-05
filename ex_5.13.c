#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define MAXPTR 100
#define ALLOCSIZE 10000

char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
        return allocp += n, allocp - n;
    else
        return NULL;
}

int my_getline(char s[], int lim)
{
    int c, i = 0;

    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

int main(int argc, char *argv[])
{
    int n = 10;
    int total = 0;
    int pos;
    char line[MAXLINE];
    char *lineptr[MAXPTR];
    char *p;

    if (argc > 1 && argv[1][0] == '-')
        n = atoi(argv[1] + 1);

    if (n <= 0)
        n = 10;

    if (n > MAXPTR)
        n = MAXPTR;

    while (my_getline(line, MAXLINE) > 0) {
        if ((p = alloc(strlen(line) + 1)) == NULL)
            break;
        strcpy(p, line);
        lineptr[total % n] = p;
        total++;
    }

    if (total == 0)
        return 0;

    if (total < n)
        n = total;

    pos = (total - n) % n;

    while (n-- > 0) {
        printf("%s", lineptr[pos]);
        pos = (pos + 1);
    }

    return 0;
}
