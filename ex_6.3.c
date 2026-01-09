#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

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

struct linenode {
    int line;
    struct linenode *next;
};

struct tnode {
    char *word;
    struct linenode *lines;
    struct tnode *left;
    struct tnode *right;
};

char *noise[] = {
    "And",  "As", "But", "For", "Like", "Nor", "Or",  "So",  "The",
    "Then", "To", "Too", "Yet", "and",  "as",  "but", "for", "like",
    "nor",  "or", "so",  "the", "then", "to",  "too", "yet",
};
#define NOISE_LEN (sizeof(noise) / sizeof(noise[0]))

int lineno = 1;

int getword(char *word, int lim);
int is_noise(char *word);

struct tnode *addtree(struct tnode *p, char *w, int line);
struct linenode *addline(struct linenode *p, int line);

void treeprint(struct tnode *p);
char *str_dup(char *s);

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !is_noise(word))
            root = addtree(root, word, lineno);
    }

    treeprint(root);
    return 0;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch())) {
        if (c == '\n')
            lineno++;
    }

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

int is_noise(char *word)
{
    for (int i = 0; i < NOISE_LEN; i++)
        if (strcmp(word, noise[i]) == 0)
            return 1;
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = str_dup(w);
        p->lines = NULL;
        p->lines = addline(p->lines, line);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->lines = addline(p->lines, line);
    } else if (cond < 0) {
        p->left = addtree(p->left, w, line);
    } else {
        p->right = addtree(p->right, w, line);
    }
    return p;
}

struct linenode *addline(struct linenode *p, int line)
{
    if (p == NULL) {
        p = (struct linenode *)malloc(sizeof(struct linenode));
        p->line = line;
        p->next = NULL;
    } else if (p->line != line) {
        p->next = addline(p->next, line);
    }
    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (struct linenode *l = p->lines; l != NULL; l = l->next)
            printf(" %d", l->line);
        printf("\n");
        treeprint(p->right);
    }
}

char *str_dup(char *s)
{
    char *p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
