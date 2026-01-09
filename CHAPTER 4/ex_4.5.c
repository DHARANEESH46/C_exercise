/*Add access to library functions like sin, exp, and pow.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'
#define NAME    'n'
#define MAXVAL  100
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
void clear(void);
int getch(void);
void ungetch(int);

int sp = 0;
double val[MAXVAL];

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {

        case NUMBER:
            push(atof(s));
            break;

        case NAME:      //functions in math.h
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0) {
                op2 = pop();
                push(pow(pop(), op2));
            } else
                printf("error: unknown function %s\n", s);
            break;

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
            push((int)pop() % (int)op2);
            break;

        case 'c':
            clear();
            break;

        case '\n':
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

void clear(void)
{
    sp = 0;
}

int getop(char s[])
{
    int i = 0, c;

    while ((c = getch()) == ' ' || c == '\t');

    if (isalpha(c)) {
        s[i++] = c;
        while (isalpha(s[i++] = c = getch()));
        s[i - 1] = '\0';
        if (c != EOF)
            ungetch(c);
        return NAME;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    s[i++] = c;

    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';
        }
        s[i++] = next;
    }

    while (isdigit(s[i++] = c = getch()));
    if (c == '.')
        while (isdigit(s[i++] = c = getch()));

    s[i - 1] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

