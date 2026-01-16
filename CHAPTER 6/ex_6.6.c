/*Implement a simple version of the #define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section. You may also find
getch and ungetch helpful.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 100

struct nlist {
    char *name;
    char *defn;
    struct nlist *next;
};

static struct nlist *hashtab[HASHSIZE];

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
}

unsigned hash(char *s)
{
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        np->name = strdup(name);
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

int main(void)
{
    int c;
    char word[MAXWORD];
    int i;
    struct nlist *np;

    while ((c = getch()) != EOF) {

        if (c == '/') {
            int d = getch();
            if (d == '/') {               
                putchar(c); putchar(d);
                while ((c = getch()) != '\n' && c != EOF)
                    putchar(c);
                putchar('\n');
                continue;
            } else if (d == '*') {        
                putchar(c); putchar(d);
                while ((c = getch()) != EOF) {
                    putchar(c);
                    if (c == '*' && (d = getch()) == '/') {
                        putchar(d);
                        break;
                    }
                    ungetch(d);
                }
                continue;
            }
            ungetch(d);
        }

        if (c == '"') {
            putchar(c);
            while ((c = getch()) != '"' && c != EOF) {
                putchar(c);
                if (c == '\\')
                    putchar(getch());
            }
            putchar('"');
            continue;
        }

        if (c == '#') {
            putchar(c);
            i = 0;
            while (isalpha(c = getch()))
                word[i++] = c;
            word[i] = '\0';
            printf("%s", word);

            if (strcmp(word, "define") == 0) {
                char name[MAXWORD], defn[MAXWORD];
                while (isspace(c))
                    putchar(c), c = getch();

                i = 0;
                while (isalnum(c) || c == '_') {
                    name[i++] = c;
                    putchar(c);
                    c = getch();
                }
                name[i] = '\0';

                while (isspace(c))
                    putchar(c), c = getch();

                i = 0;
                while (c != '\n') {
                    defn[i++] = c;
                    putchar(c);
                    c = getch();
                }
                defn[i] = '\0';
                install(name, defn);
                putchar('\n');
                continue;
            }
        }

        if (isalpha(c) || c == '_') {
            i = 0;
            word[i++] = c;
            while (isalnum(c = getch()) || c == '_')
                word[i++] = c;
            word[i] = '\0';
            ungetch(c);

            if ((np = lookup(word)) != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);

            continue;
        }

        putchar(c);
    }

    return 0;
}
