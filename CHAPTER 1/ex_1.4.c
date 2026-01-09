/*Write a program to print the corresponding Celsius to Fahrenheit table.*/

#include <stdio.h>

int main() {
    float celsius, fahr;
    float lower, upper, step;

    lower = 0;  
    upper = 100;  
    step = 10;    

    printf("%7s %7s\n", "Celsius", "Fahr");
    printf("-------------------\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = (celsius * 9.0 / 5.0) + 32.0;
        printf("%7.1f %7.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
