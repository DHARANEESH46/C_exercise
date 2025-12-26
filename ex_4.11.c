#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'

int getop(char s[])
{
    static int lastc = 0;  
    int c;
    int i = 0;

    if(lastc==0)
        c=getchar();
    else{
        c=lastc;
        lastc=0;
    }
    
    while ((c = getch()) == ' ' || c == '\t');

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') {
        lastc = 0;
        return c;
    }

    if (c == '-') {
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            lastc = next;
            return '-';
        }
        s[i++] = c;
        c = next;
    }

    while (isdigit(c)) {
        s[i++] = c;
        c = getchar();
    }

    if (c == '.') {
        s[i++] = c;
        while (isdigit(c = getchar()))
            s[i++] = c;
    }

    s[i] = '\0';
    if(c!=EOF)
        lastc = c;   
    return NUMBER;
}
