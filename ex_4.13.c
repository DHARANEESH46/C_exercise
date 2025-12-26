#include <stdio.h>

void reverse(char s[],int len){

    static int st=0;
    if(st<len){
        char temp=s[st];
        s[st]=s[len];
        s[len]=temp;
        st++;
        reverse(s,--len);
    }
}

int main(){
    char s[1000]="hello";
    int i;

    for(i=0;s[i]!='\0';i++);
    i--;
    reverse(s,i);

    printf("%s",s);
}