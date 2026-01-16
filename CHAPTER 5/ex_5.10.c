/*Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL  100
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char[]);

int sp = 0;
double val[MAXVAL];

int main(int argc, char *argv[])
{
    double op2;
    char s[MAXOP];

    while (--argc > 0) {
        ungets(" ");
        ungets(*++argv);

        switch (getop(s)) {

        case NUMBER:
            push(atof(s));
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
            if ((int)op2 != 0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor for modulus\n");
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    printf("\t%.8g\n", pop());
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


int getop(char s[])
{
    int i = 0, c;

    while ((c = getch()) == ' ' || c == '\t');

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';
        }
        s[++i] = c = next;
    }

    while (isdigit(s[++i] = c = getch()));

    if (c == '.')
        while (isdigit(s[++i] = c = getch()));

    s[i] = '\0';

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
    else
        printf("ungetch: too many characters\n");
}

void ungets(char s[])
{
    int i = strlen(s);

    while (i > 0)
        ungetch(s[--i]);
}