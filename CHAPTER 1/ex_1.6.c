/*Verify that the expression getchar() != EOF is 0 or 1.*/

#include <stdio.h>

int main() {
    int result;

    result = (getchar() != EOF);
    printf("%d", result);

    return 0;
}
