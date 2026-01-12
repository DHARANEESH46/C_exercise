#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 100

struct nlist {
    char *name;
    char *defn;
    struct nlist *next;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
void print_table(void);

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

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
        if (np == NULL)
            return NULL;

        np->name = strdup(name);
        if (np->name == NULL)
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);  
    }

    np->defn = strdup(defn);
    if (np->defn == NULL)
        return NULL;

    return np;
}

void undef(char *name)
{
    unsigned hashval = hash(name);
    struct nlist *np = hashtab[hashval];
    struct nlist *prev = NULL;

    while (np != NULL) {
        if (strcmp(name, np->name) == 0) {

            if (prev == NULL)
                hashtab[hashval] = np->next;   
            else
                prev->next = np->next;         

            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
        prev = np;
        np = np->next;
    }
}

void print_table(void)
{
    struct nlist *np;
    int i;

    for (i = 0; i < HASHSIZE; i++) {
        for (np = hashtab[i]; np != NULL; np = np->next)
            printf("%s -> %s\n", np->name, np->defn);
    }
}

int main(void)
{
    install("MAX", "100");
    install("MIN", "1");
    install("COUNT", "10");
    install("TOTAL", "500");
    install("TEMP", "25");

    printf("Hash table after install:\n");
    print_table();

    undef("MAX");
    install("TOTAL","600");
    undef("COUNT");
    undef("NOT_PRESENT");

    printf("\nHash table after modifications:\n");
    print_table();

    return 0;
}
