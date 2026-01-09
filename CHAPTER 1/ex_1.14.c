/*Write a program to print a histogram of the frequencies of different characters
in its input.*/

#include <stdio.h>

#define MAX 128

int main() {
    int c;
    int freq[MAX];

    for (int i = 0; i < MAX; i++)
        freq[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c < MAX)
            ++freq[c];
    }

    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            if (i == '\n')
                printf("\\n  |");
            else if (i == '\t')
                printf("\\t  |");
            else if (i == ' ')
                printf("' ' |");
            else
                printf("%c   |", i);

            for (int j = 0; j < freq[i]; j++)
                putchar('*');
            putchar('\n');
        }
    }

    return 0;
}
