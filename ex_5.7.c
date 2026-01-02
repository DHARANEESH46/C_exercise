#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXLEN 1000      /* max length of any input line */
char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], char linebuf[][MAXLEN], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);       /* sort input lines */


int main()
{
    int nlines;         /* number of input lines read */
    char linebuf[MAXLINES][MAXLEN]; 

    if ((nlines = readlines(lineptr,linebuf, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }  
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


int my_getline(char *, int);

int readlines(char *lineptr[], char linebuf[][MAXLEN], int maxlines)
{
    int len, nlines = 0;

    while ((len = my_getline(linebuf[nlines], MAXLEN)) > 0) {

        if (nlines >= maxlines)
            return -1;

        linebuf[nlines][len-1] = '\0';   /* remove newline */
        lineptr[nlines] = linebuf[nlines];  /* point to this line */
        nlines++;
    }

    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    printf("\nSorted lines:\n");
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}


int my_getline(char *s, int lim)
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) /* do nothing if array contains */
        return;              /* fewer than two elements */
    
    swap(v, left, (left + right)/2);
    last = left;
    
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);        
    
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}