#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>   

#define MAXLINE 1000
#define MAXVAL  100
#define NUMBER  '0'
#define NAME    'n'
#define VAR     'v'

int sp = 0;
double val[MAXVAL];

double vars[26];        
char lastvar = 0;

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

int my_getline(char s[], int max)
{
    int c, i = 0;
    while (i < max - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int getop(char s[], char line[], int *pos)
{
    int i = 0;

    while (line[*pos] == ' ' || line[*pos] == '\t')
        (*pos)++;

    s[0] = line[*pos];
    s[1] = '\0';

    if (isalpha(line[*pos])) {
        while (isalpha(line[*pos]))
            s[i++] = line[(*pos)++];
        s[i] = '\0';
        return NAME;
    }

    if (islower(s[0]) && s[1] == '\0')
        return VAR;


    if (!isdigit(line[*pos]) && line[*pos] != '.' && line[*pos] != '-') {
        (*pos)++;
        return s[0];
    }

    if (line[*pos] == '-' && !isdigit(line[*pos + 1]) && line[*pos + 1] != '.') {
        (*pos)++;
        return '-';
    }

    if (line[*pos] == '-')
        s[i++] = line[(*pos)++];

    while (isdigit(line[*pos]))
        s[i++] = line[(*pos)++];

    if (line[*pos] == '.') {
        s[i++] = line[(*pos)++];
        while (isdigit(line[*pos]))
            s[i++] = line[(*pos)++];
    }

    s[i] = '\0';
    return NUMBER;
}

int main(void)
{
    int type;
    double op2;
    char token[MAXLINE];
    char line[MAXLINE];
    int pos;

    while (my_getline(line, MAXLINE) > 0) {
        pos = 0;

        while ((type = getop(token, line, &pos)) != '\n') {

            switch (type) {

            case NUMBER:
                push(atof(token));
                break;

            case VAR:
                lastvar = token[0];
                push(vars[lastvar - 'a']);
                break;

            case '=':
                if (lastvar >= 'a' && lastvar <= 'z')
                    vars[lastvar - 'a'] = pop();
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

            case NAME:
                if (strcmp(token, "sin") == 0)
                    push(sin(pop()));
                else if (strcmp(token, "cos") == 0)
                    push(cos(pop()));
                else if (strcmp(token, "exp") == 0)
                    push(exp(pop()));
                else if (strcmp(token, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                    printf("error: unknown function %s\n", token);
                break;

            default:
                printf("error: unknown command %s\n", token);
                break;
            }
        }

        printf("\t%.8g\n", pop());
    }

    return 0;
}
