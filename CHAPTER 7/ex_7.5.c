/*Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
the input and number conversion.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP   100
#define MAXVAL  100

void push(double);
double pop(void);

int sp = 0;
double val[MAXVAL];

int main(void)
{
    char s[MAXOP];
    double op2, num;

    printf("Enter postfix expression:\n");

    while (scanf("%s", s) == 1) {

        if (sscanf(s, "%lf", &num) == 1) {
            push(num);
            continue;
        }

        switch (s[0]) {

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;

        case '%':
            op2 = pop();
            if ((int)op2 != 0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor for modulus\n");
            break;

        case '=':   
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
