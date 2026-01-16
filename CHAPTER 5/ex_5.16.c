/*Add the -d (``directory order'') option, which makes comparisons only on
letters, numbers and blanks. Make sure it works in conjunction with -f.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMERIC 1
#define DECR    2
#define FOLD    4
#define MDIR    8
#define LINES   1000

#define MAXLEN  1000
#define ALLOCSIZE 10000

static char option = 0;
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *lineptr[LINES];

int mgetline(char s[], int lim);
char *alloc(int n);
void afree(char *p);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int decr);
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
int charcmp(char *s, char *t);

int main(int argc, char *argv[])
{
    int nlines, c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n': option |= NUMERIC; break;
                case 'r': option |= DECR; break;
                case 'f': option |= FOLD; break;
                case 'd': option |= MDIR; break;
                default:
                    printf("sort: illegal option %c\n", c);
                    rc = -1;
                    argc = 1;
                    break;
            }
        }
    }

    if (argc)
        printf("Usage: sort -dfnr\n");
    else {
        if ((nlines = readlines(lineptr, LINES)) > 0) {
            if (option & NUMERIC)
                myqsort((void **)lineptr, 0, nlines - 1,
                        (int (*)(void *, void *))numcmp);
            else
                myqsort((void **)lineptr, 0, nlines - 1,
                        (int (*)(void *, void *))charcmp);

            writelines(lineptr, nlines, option & DECR);
        } else {
            printf("input too big to sort\n");
            rc = -1;
        }
    }

    return rc;
}

int mgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return NULL;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN], *p;

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len-1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines, int decr)
{
    int i;
    if (decr)
        for (i = nlines-1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
}

void myqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right) return;

    swap(v, left, (left+right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    myqsort(v, left, last-1, comp);
    myqsort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

int charcmp(char *s, char *t)
{
    char a, b;
    do {
        if (option & MDIR) {
            while (*s && !isalnum(*s) && *s != ' ') s++;
            while (*t && !isalnum(*t) && *t != ' ') t++;
        }

        a = (option & FOLD) ? tolower(*s) : *s;
        b = (option & FOLD) ? tolower(*t) : *t;

        if (a) s++;
        if (b) t++;

        if (a == b && a == '\0') return 0;
    } while (a == b);

    return a - b;
}
