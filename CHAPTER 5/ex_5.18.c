/*Make dcl recover from input errors.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void skipline(void)
{
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}



void _dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("syntax error: missing )\n");
            skipline();
            return;
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else {
        printf("syntax error: expected name or (dcl)\n");
        skipline();
        return;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void dcl(void)
{
    int ns = 0;

    while (gettoken() == '*')
        ns++;

    if (tokentype == '\n') {
        printf("syntax error: incomplete declaration\n");
        skipline();
        return;
    }

    _dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t');

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            tokentype = '(';
            ungetc(c, stdin);
            return '(';
        }
    }
    else if (c == '[') {
        *p++=c;
        while ((*p++ = getchar()) != ']');
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
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

int main(void)
{
    int type;

    while ((type = gettoken()) != EOF) {

        if (type == '\n')
            continue;

        strcpy(datatype, token);
        out[0] = '\0';

        dcl();

        if (tokentype == '\n')
            printf("%s: %s %s\n", name, out, datatype);
        else {
            printf("syntax error in declaration\n");
            skipline();
        }
    }
    return 0;
}
