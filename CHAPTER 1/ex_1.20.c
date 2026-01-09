/*Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
Should n be a variable or a symbolic parameter?*/

#include <stdio.h>

#define MAX 1000
#define n 8   

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

void detab(char s[])
{
    int i = 0;
    int col = 0;  

    while (s[i] != '\0') {

        if (s[i] == '\t') {
            int spaces = n - (col % n);

            while (spaces-- > 0) {
                putchar(' ');
                col++;
            }
        }
        else {
            putchar(s[i]);
            col++;
        }
        i++;
    }
}

int main()
{
    char line[MAX];

    while (my_getline(line, MAX) > 0) {
        detab(line);
    }

    return 0;
}
