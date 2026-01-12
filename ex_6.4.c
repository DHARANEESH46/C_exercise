#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

char buf[BUFSIZE];
int bufp = 0;

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *p, char *w);
void tree_to_array(struct tnode *p, struct tnode **arr, int *index);
void print_by_frequency(struct tnode **arr, int n);

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    *w++ = tolower(c);
    while (--lim > 0) {
        c = getch();
        if (!isalnum(c)) {
            ungetch(c);
            break;
        }
        *w++ = tolower(c);
    }
    *w = '\0';
    return word[0];
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void tree_to_array(struct tnode *p, struct tnode **arr, int *index)
{
    if (p != NULL) {
        tree_to_array(p->left, arr, index);
        arr[(*index)++] = p;
        tree_to_array(p->right, arr, index);
    }
}

void print_by_frequency(struct tnode **arr, int n)
{
    int i, j;
    struct tnode *temp;

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (arr[i]->count < arr[j]->count) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }

    for (i = 0; i < n; i++)
        printf("%4d %s\n", arr[i]->count, arr[i]->word);
}

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    struct tnode *arr[10000];
    int n = 0;

    tree_to_array(root, arr, &n);
    print_by_frequency(arr, n);

    return 0;
}
