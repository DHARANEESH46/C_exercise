/*Extend atof to handle scientific notation of the form 123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.*/

#include <stdio.h>
#include <ctype.h>

double atof(char s[])
{
    double val = 0.0;
    double power = 1.0;
    int i = 0;
    int sign = 1;
    int exp_sign = 1;
    int exp = 0;

    while (isspace(s[i]))
        i++;

    if (s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        i++;
    }

    if (s[i] == '.')
        i++;

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
        i++;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;

        if (s[i] == '+' || s[i] == '-') {
            exp_sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        while (isdigit(s[i])) {
            exp = 10 * exp + (s[i] - '0');
            i++;
        }

        while (exp > 0) {
            if (exp_sign == 1)
                val *= 10.0;
            else
                val /= 10.0;
            exp--;
        }
    }

    return val;
}

int main()
{
    char s1[] = "123.45e-2";
    char s2[] = "-3.2E3";
    char s3[] = "5e0";

    printf("%f\n", atof(s1));
    printf("%f\n", atof(s2));
    printf("%f\n", atof(s3));

    return 0;
}
