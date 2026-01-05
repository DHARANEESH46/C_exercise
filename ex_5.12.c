#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

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

int nexttab(int col, int m, int n)
{
    if (col < m)
        return m;

    return m + ((col - m) / n + 1) * n;
}


void detab(char line[], int m, int n)
{
    int i, col, spaces;

    col = 0;
    for (i = 0; line[i] != '\0'; i++) {

        if (line[i] == '\t') {
            spaces = nexttab(col, m, n) - col;
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


void entab(char line[], int m, int n)
{
    int i, col, space;

    col = space = 0;

    for (i = 0; line[i] != '\0'; i++) {

        if (line[i] == ' ') {
            space++;
        } else {
            while (space > 0) {
                int next = nexttab(col, m, n);

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
    int m = 0;     
    int n = 8;    
    int i;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-')
            m = atoi(&argv[i][1]);
        else if (argv[i][0] == '+')
            n = atoi(&argv[i][1]);
    }

    if (n <= 0)
        n = 8;

    while (getline1(line, MAXLINE) > 0) 
        detab(line, m, n);
        //entab(line, m, n);
    return 0;
}



