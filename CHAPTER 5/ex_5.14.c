/*Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *lineptr[MAXLINES];

int my_getline(char *, int);
char *alloc(int);
void writelines(char *[], int);
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int revcmp(void *, void *);

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
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

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len + 1)) == NULL)
            return -1;
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    _qsort(v, left, last - 1, comp);
    _qsort(v, last + 1, right, comp);
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int revcmp(void *a, void *b)
{
    return -strcmp(a, b);
}

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("input too big\n");
        return 1;
    }

    if (numeric && reverse)
        _qsort((void**)lineptr, 0, nlines-1,
              (int (*)(void*,void*))revcmp);
    else if (numeric)
        _qsort((void**)lineptr, 0, nlines-1,
              (int (*)(void*,void*))numcmp);
    else if (reverse)
        _qsort((void**)lineptr, 0, nlines-1, revcmp);
    else
        _qsort((void**)lineptr, 0, nlines-1,
              (int (*)(void*,void*))strcmp);

    writelines(lineptr, nlines);
    return 0;
}
