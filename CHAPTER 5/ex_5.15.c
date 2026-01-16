/*Add the option -f to fold upper and lower case together, so that case
distinctions are not made during sorting; for example, a and A compare equal.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000

#define NUMERIC 1
#define DECR    2
#define FOLD    4

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *lineptr[MAXLINES];
static char option = 0;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    return NULL;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int mgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int charcmp(char *s, char *t)
{
    for (; tolower(*s)==tolower(*t); s++, t++)
        if (*s=='\0') return 0;
    return tolower(*s) - tolower(*t);
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len-1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int (*comparator)(void *, void *);
int reverse = 0;

int r_compare(void *a, void *b)
{
    int res = comparator(a, b);
    return reverse ? -res : res;
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right) return;

    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last-1, comp);
    _qsort(v, last+1, right, comp);
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int main(int argc, char *argv[])
{
    int numeric=0, fold=0;
    int nlines;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0]=='-') {
            for (int j=1; argv[i][j]; j++)
                switch(argv[i][j]) {
                    case 'n': numeric=1; break;
                    case 'r': reverse=1; break;
                    case 'f': fold=1; break;
                    default:
                        printf("sort: illegal option %c\n", argv[i][j]);
                        return 1;
                }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) <= 0) {
        printf("input too big or empty\n");
        return 1;
    }

    if (numeric)
        comparator = (int (*)(void*,void*)) numcmp;
    else if (fold)
        comparator = (int (*)(void*,void*)) charcmp;
    else
        comparator = (int (*)(void*,void*)) strcmp;

    _qsort((void **)lineptr, 0, nlines-1, r_compare);

    writelines(lineptr, nlines);
    return 0;
}
