#include <stdio.h>
#include <ctype.h>

#define MAXCOL 60   
int main(void)
{
    int c;
    int col = 0;

    while ((c = getchar()) != EOF) {

        if (col >= MAXCOL) {
            putchar('\n');
            col = 0;
        }

        if (isprint(c)) {
            putchar(c);
            col++;
        } 
        else {
            printf("[0x%02X]", c);
            if(c=='\n')
                putchar('\n');
            col += 6;   
        }

        if (c == '\n') {
            col = 0;
        }
    }

    return 0;
}
