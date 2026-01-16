#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMERIC 1
#define DECR    2
#define FOLD    4
#define MDIR    8

#define MAXFIELDS 10
#define MAXLEN 1000
#define LINES 1000
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *lineptr[LINES];

/* field configuration */
int fieldpos[MAXFIELDS];
int fieldopt[MAXFIELDS];
int nfields = 0;

/* function prototypes */
int mgetline(char s[], int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int decr);
void myqsort(void *v[], int left, int right,
             int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
int charcmp(char *s, char *t);
char *getfield(char *line, int fieldno);
int fieldcmp(void *a, void *b);
char *alloc(int n);

int main(int argc, char *argv[])
{
    int nlines;
    int c;

    /* parse command line */
    while (--argc > 0 && (*++argv)[0] == '-') {
        if ((*argv)[1] == 'k') {
            int f = atoi(&(*argv)[2]);
            fieldpos[nfields] = f;
            fieldopt[nfields] = 0;

            while ((c = *++argv[0])) {
                switch (c) {
                case 'n': fieldopt[nfields] |= NUMERIC; break;
                case 'd': fieldopt[nfields] |= MDIR; break;
                case 'f': fieldopt[nfields] |= FOLD; break;
                case 'r': fieldopt[nfields] |= DECR; break;
                }
            }
            nfields++;
        }
    }

    if ((nlines = readlines(lineptr, LINES)) < 0) {
        printf("input too big to sort\n");
        return 1;
    }

    myqsort((void **)lineptr, 0, nlines - 1, fieldcmp);
    writelines(lineptr, nlines, 0);

    return 0;
}

/* getline */
int mgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 &&
         (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

/* read lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p;

    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines ||
            (p = alloc(len)) == NULL)
            return -1;

        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* write lines */
void writelines(char *lineptr[], int nlines, int decr)
{
    int i;
    if (decr)
        for (i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
}

/* qsort */
void myqsort(void *v[], int left, int right,
             int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numeric comparison */
int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

/* character comparison with -d and -f */
int charcmp(char *s, char *t)
{
    char a, b;

    do {
        if (fieldopt[nfields-1] & MDIR) {
            while (*s && !isalnum(*s) && *s != ' ')
                s++;
            while (*t && !isalnum(*t) && *t != ' ')
                t++;
        }

        a = (fieldopt[nfields-1] & FOLD) ?
             tolower(*s) : *s;
        b = (fieldopt[nfields-1] & FOLD) ?
             tolower(*t) : *t;

        if (a) s++;
        if (b) t++;

        if (a == b && a == '\0')
            return 0;
    } while (a == b);

    return a - b;
}

/* extract Nth field */
char *getfield(char *line, int fieldno)
{
    static char field[MAXLEN];
    int i = 1;

    while (*line && i < fieldno) {
        while (*line && !isspace(*line))
            line++;
        while (*line && isspace(*line))
            line++;
        i++;
    }

    int j = 0;
    while (*line && !isspace(*line))
        field[j++] = *line++;

    field[j] = '\0';
    return field;
}

/* field comparison */
int fieldcmp(void *a, void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    for (int i = 0; i < nfields; i++) {
        char *f1 = getfield(s1, fieldpos[i]);
        char *f2 = getfield(s2, fieldpos[i]);

        int result;
        if (fieldopt[i] & NUMERIC)
            result = numcmp(f1, f2);
        else
            result = charcmp(f1, f2);

        if (result != 0)
            return result;
    }
    return 0;
}

/* allocator */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    return NULL;
}
