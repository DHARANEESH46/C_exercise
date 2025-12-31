#include<stdio.h>

#define MAX 1000
#define MAXLINES 1000


int my_getline(char s[], int lim)
{
    int c, i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 1)
            *s++=c;
        ++i;
    }

    if (c == '\n') {
        if (i < lim - 1)
            *s++=c;
        ++i;
    }

    if (i < lim)
        *s='\0';
    else
        --s;
        *s='\0';

    return i;
}

int main(void)
{
    char line[MAX];
    char store[MAXLINES][MAX];   
    int len = 0;
    int count = 0;

    while ((len = my_getline(line, MAX)) > 0) {
            int i = 0;
            while ((store[count][i] = line[i]) != '\0')
                i++;
            count++;
    }

    printf("\n");
    for (int i = 0; i < count; i++)
        printf("%s", store[i]);

    return 0;
}