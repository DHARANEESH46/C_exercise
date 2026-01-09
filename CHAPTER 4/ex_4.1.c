/*Write the function strindex(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none.*/

#include <stdio.h>

int strindex(char s[], char t[])
{
    int i, j, k;
    int pos = -1;  

    for (i = 0; s[i] != '\0'; i++) {
        k=i;
        for (j =0; t[j] != '\0'; j++){
            if (s[k]==t[j])
                k++;
            else
                break;
        }

        if (t[j] == '\0') 
            pos = i;   
    }

    return pos;
}

int main()
{
    char s[] = "aba";
    char t[] = "ba";

    int result = strindex(s, t);

    printf("%d\n", result);

    return 0;
}
