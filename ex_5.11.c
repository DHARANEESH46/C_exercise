#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXTABS 100

void detab(char line[], int tabs[], int ntabs)
{
    int i, col, spaces;

    col = 0;
    for (i = 0; line[i] != '\0'; i++) {

        if (line[i] == '\t') {
            spaces = nexttab(col, tabs, ntabs) - col;
            while (spaces-- > 0) {
                putchar(' ');
                col++;
            }
        } else {
            putchar(line[i]);
            col++;
        }
    }
}

int my_getline(char s[], int lim)
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 1)
            s[i] = c;
        i++;
    }

    if (c == '\n') {
        if (i < lim - 1)
            s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}

int nexttab(int col, int tabs[], int ntabs)
{
    int i;

    for (i = 0; i < ntabs; i++)
        if (tabs[i] > col)
            return tabs[i];

    return col + (8 - col % 8);
}

void entab(char line[], int tabs[], int ntabs)
{
    int i, col, space;

    col = space = 0;

    for (i = 0; line[i] != '\0'; i++) {

        if (line[i] == ' ') {
            space++;
        } else {
            while (space > 0) {
                int next = nexttab(col, tabs, ntabs);
                if (col + space >= next) {
                    putchar('\\');
                    putchar('t');
                    space -= (next - col);
                    col = next;
                } else {
                    putchar(' ');
                    space--;
                    col++;
                }
            }
            putchar(line[i]);
            col++;
        }
    }
}


int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int tabs[MAXTABS];
    int ntabs = 0;
    int i;

    for (i = 1; i < argc; i++)
        tabs[ntabs++] = atoi(argv[i]);

    while (my_getline(line, MAXLINE) > 0)
        detab(line, tabs, ntabs);

    return 0;
}

