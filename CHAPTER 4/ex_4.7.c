/*Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'
#define VAR     '1'

int getop(char []);
void push(double);
double pop(void);

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

double vars[26];
double last = 0.0;

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

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int varname = -1;

    while ((type = getop(s)) != EOF) {
        switch (type) {

        case NUMBER:
            push(atof(s));
            break;

        case VAR:
            if (s[0] >= 'a' && s[0] <= 'z')
                push(vars[s[0] - 'a']);
            else if (s[0] == 'v')
                push(last);
            varname = s[0];
            break;

        case '=':
            if (varname >= 'a' && varname <= 'z')
                vars[varname - 'a'] = pop();
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
            if (op2 != 0.0)
                push(fmod(pop(),op2));
            else
                printf("error: zero divisor for modulus\n");
            break;

        case '\n':
            last = pop();
            printf("\t%.8g\n", last);
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i = 0, c;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    s[0] = c;
    s[1] = '\0';

    if (islower(c) || c == 'v')
        return VAR;

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));

    if (c == '.')
        while (isdigit(s[++i] = c = getch())) ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100
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

void ungets(const char s[])
{
    int i = strlen(s);

    while (i > 0)
        ungetch(s[--i]);
}