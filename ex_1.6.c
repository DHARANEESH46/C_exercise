#include <stdio.h>

int main() {
    int result;

    result = (getchar() != EOF);
    printf("%d", result);

    return 0;
}
