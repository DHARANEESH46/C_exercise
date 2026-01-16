/*Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))
#define BUFSIZE 100


struct key{
    char * word;
    int count;
}keytab[] = {{"auto", 0},{"break", 0},{"case", 0},{"char", 0},{"const", 0},{"continue", 0},
            {"default", 0},{"unsigned", 0},{"void", 0},{"volatile", 0},{"while", 0}};


char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()));

    if (c == EOF)
        return EOF;

    if (c == '/') {
        int d = getch();
        if (d == '/') {           
            while ((c = getch()) != '\n' && c != EOF);

            return getword(word, lim);   
        } 
        else if (d == '*') {     
            while ((c = getch()) != EOF) 
            {
                if (c == '*') {
                    if ((d = getch()) == '/')
                        break;
                    else
                        ungetch(d);
                }
            }
            return getword(word, lim);   
        } 
        else {
            ungetch(d);           
        }
    }

    if (c == '"') {
        while ((c = getch()) != '"' && c != EOF);
        return getword(word, lim);
    }

    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF);
        return getword(word, lim);
    }

    if (isalpha(c) || c == '_') {
        *w++ = c;
        while (--lim > 0) {
            c = getch();
            if (isalnum(c) || c == '_')
                *w++ = c;
            else {
                ungetch(c);
                break;
            }
        }
    }

    *w = '\0';

    return word[0];
}


int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word,tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}


int main()
{
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",keytab[n].count, keytab[n].word);
    return 0;
}

