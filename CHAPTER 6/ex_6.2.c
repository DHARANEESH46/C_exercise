/*Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100
#define BUFSIZE 100
#define NR_OF_TYPES (sizeof(data_types) / sizeof(data_types[0]))

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

struct tree_node {
    char *word;
    struct tree_node *left;
    struct tree_node *right;
};

struct list_node {
    struct tree_node *var_group;
    struct list_node *next;
};

struct tree_node *add_to_tree(struct tree_node *node_p, char *word);
void print_tree(struct tree_node *node_p);

struct list_node *add_to_list(struct list_node *list_node_p, char *word);
void print_list(struct list_node *node_p);

char *str_dup(char *src);

void skip_blanks(void);
void skip_comments(void);
void skip_chars_between(char start, char end);
void skip_char_literal(void);
void skip_string_literal(void);

int get_word(char *word, int max_word_len);
int bin_search(char *word, char *arr[], int arr_len);
int count_tree_nodes(struct tree_node *node_p);

char *data_types[] = {
    "char", "double", "float", "int", "long", "short", "void",
};

int num = 6;

int main(int argc, char *argv[])
{
    if (argc > 2) {
        printf("Usage: %s [N]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        if (!isdigit(argv[1][0])) {
            printf("Error: argument must be a number\n");
            return EXIT_FAILURE;
        }
        num = atoi(argv[1]);
        if (num < 0) {
            printf("Error: N must be >= 0\n");
            return EXIT_FAILURE;
        }
    }

    int n;
    struct list_node *list_root = NULL;
    char word[MAX_WORD_LEN];

    while (get_word(word, MAX_WORD_LEN) != EOF) {
        if ((n = bin_search(word, data_types, NR_OF_TYPES)) >= 0) {
            do {
                if (get_word(word, MAX_WORD_LEN) != EOF &&
                    (isalpha(word[0]) || word[0] == '_')) {
                    list_root = add_to_list(list_root, word);
                }
            } while (get_word(word, MAX_WORD_LEN) == ',');
        }
    }

    print_list(list_root);
    return EXIT_SUCCESS;
}

char *str_dup(char *src)
{
    char *dest = (char *)malloc(strlen(src) + 1);
    if (dest != NULL)
        strcpy(dest, src);
    return dest;
}

void skip_blanks(void)
{
    int c;
    while (isblank(c = getch()))
        ;
    ungetch(c);
}

void skip_comments(void)
{
    int c = getch();
    if (c == '/') {
        int d = getch();
        if (d == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
        } else if (d == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*' && (d = getch()) == '/')
                    break;
                else
                    ungetch(d);
            }
        } else {
            ungetch(d);
        }
    }
    ungetch(c);
}

void skip_chars_between(char start, char end)
{
    int c = getch();
    if (c == start) {
        while ((c = getch()) != EOF) {
            if (c == '\\')
                getch();
            else if (c == end)
                return;
        }
    }
    ungetch(c);
}

void skip_char_literal(void) { skip_chars_between('\'', '\''); }
void skip_string_literal(void) { skip_chars_between('"', '"'); }

int get_word(char *word, int max_word_len)
{
    skip_blanks();
    skip_comments();
    skip_char_literal();
    skip_string_literal();

    int c = getch();
    int i = 0;

    if (c != EOF)
        word[i++] = c;

    if (!isalpha(c) && c != '_') {
        word[i] = '\0';
        return c;
    }

    while ((isalnum(c = getch()) || c == '_') && i < max_word_len)
        word[i++] = c;

    ungetch(c);
    word[i] = '\0';

    return word[0];
}

int bin_search(char *word, char *arr[], int arr_len)
{
    int low = 0, high = arr_len - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cond = strcmp(word, arr[mid]);

        if (cond < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

struct tree_node *add_to_tree(struct tree_node *node_p, char *word)
{
    int cond;

    if (node_p == NULL) {
        node_p = (struct tree_node *)malloc(sizeof(struct tree_node));
        node_p->word = str_dup(word);
        node_p->left = node_p->right = NULL;
    } else if ((cond = strcmp(word, node_p->word)) != 0) {
        if (cond < 0)
            node_p->left = add_to_tree(node_p->left, word);
        else
            node_p->right = add_to_tree(node_p->right, word);
    }
    return node_p;
}

void print_tree(struct tree_node *node_p)
{
    if (node_p != NULL) {
        print_tree(node_p->left);
        puts(node_p->word);
        print_tree(node_p->right);
    }
}

int count_tree_nodes(struct tree_node *node_p)
{
    if (node_p == NULL)
        return 0;
    return 1 + count_tree_nodes(node_p->left) + count_tree_nodes(node_p->right);
}

struct list_node *add_to_list(struct list_node *list_node_p, char *word)
{
    if (list_node_p == NULL) {
        list_node_p = (struct list_node *)malloc(sizeof(struct list_node));
        list_node_p->var_group = NULL;
        list_node_p->next = NULL;
        list_node_p->var_group = add_to_tree(list_node_p->var_group, word);
    } else if (strncmp(list_node_p->var_group->word, word,
                       num) == 0) {
        list_node_p->var_group = add_to_tree(list_node_p->var_group, word);
    } else {
        list_node_p->next = add_to_list(list_node_p->next, word);
    }
    return list_node_p;
}

void print_list(struct list_node *node_p)
{
    if (node_p != NULL) {
        if (count_tree_nodes(node_p->var_group) > 1) {
            print_tree(node_p->var_group);
            putchar('\n');
        }
        print_list(node_p->next);
    }
}
