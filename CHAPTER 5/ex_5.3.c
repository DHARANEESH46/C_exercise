/*Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.*/

#include<stdio.h>

void str_cat(char *s,char *t){
    while(*s!='\0') s++;
    while(*t!='\0'){
        *s=*t;
        t++;
        s++;
    }
    *s='\0';
}
int main(){
    char s[100]="hello";
    char t[100]="iam";

    str_cat(s,t);
    printf("\n%s",s);
}