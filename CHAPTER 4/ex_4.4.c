/*Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'
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

        case '?':   //print top
            if (sp > 0)
                printf("Top: %.8g\n", val[sp - 1]);
            else
                printf("Stack empty\n");
            break;

        case 'd':   //duplicate top
            if (sp > 0)
                push(val[sp - 1]);
            else
                printf("Stack empty\n");
            break;

        case 's':   //swap top 2 elements
            if (sp >= 2) {
                double temp = val[sp - 1];
                val[sp - 1] = val[sp - 2];
                val[sp - 2] = temp;
            } else
                printf("Not enough elements to swap\n");
            break;

        case 'c':   //clear stack
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

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

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

    while (isdigit(s[++i] = c = getch()))
        ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

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
