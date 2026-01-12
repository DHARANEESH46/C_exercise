#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    int to_lower = 0;
    int to_upper = 0;

    if (strstr(argv[0], "lower") != NULL)
        to_lower = 1;
    else if (strstr(argv[0], "upper") != NULL)
        to_upper = 1;

    while ((c = getchar()) != EOF) {
        if (to_lower && isupper(c))
            c = tolower(c);
        else if (to_upper && islower(c))
            c = toupper(c);

        putchar(c);
    }

    return 0;
}
