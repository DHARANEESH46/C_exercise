/*Suppose that there will never be more than one character of pushback. Modify
getch and ungetch accordingly.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

    while ((c = getch()) == ' ' || c == '\t');

    s[0] = c;
    s[1] = '\0';

    if (islower(c) || c == 'v')
        return VAR;

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
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


int buf = 0;        
int hasbuf = 0;    

int getch(void)
{
    if (hasbuf) {
        hasbuf = 0;
        return buf;
    } else {
        return getchar();
    }
}

void ungetch(int c)
{
    if (hasbuf)
        printf("ungetch: too many characters\n");
    else {
        buf = c;
        hasbuf = 1;
    }
}