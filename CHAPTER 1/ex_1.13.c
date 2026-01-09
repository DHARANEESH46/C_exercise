/*Write a program to print a histogram of the lengths of words in its input. It is
easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.*/

#include <stdio.h>

#define MAXWORD 20   

int main() {
    int c;
    int length = 0;
    int l[MAXWORD + 1];

    for (int i = 0; i <= MAXWORD; i++)
        l[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (length > 0) {
                if (length <= MAXWORD)
                    ++l[length];
                length = 0;
            }
        } 
        else {
            ++length;
        }
    }

    for (int i = 1; i <= MAXWORD; i++) {
        if (l[i] > 0) {
            printf("%2d | ", i);
            for (int j = 0; j < l[i]; j++)
                putchar('*');
            putchar('\n');
        }
    }

    return 0;
}
