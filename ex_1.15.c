#include <stdio.h>

float fahr_to_cel(float fahr);

int main(void) {
    float fahr;
    int lower = 0;
    int upper = 300;
    int step  = 20;

    printf("Fahrenheit  Celsius\n");
    printf("-------------------\n");

    for (fahr = lower; fahr <= upper; fahr += step) {
        printf("%6.0f %10.1f\n", fahr, fahr_to_cel(fahr));
    }

    return 0;
}

float fahr_to_cel(float fahr) {
    return (5.0 / 9.0) * (fahr - 32.0);
}
