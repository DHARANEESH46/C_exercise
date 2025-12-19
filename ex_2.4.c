#include<stdio.h>

void squeeze(char a1[], char a2[])
{
int i, j,k=0,l=0;
for (i = 0; a1[i] != '\0'; i++){
    for(j=0;a2[j]!='\0';j++){
        if (a1[i]==a2[j])
            k++;
            break;
    }
    if(k==0)
        a1[l++]=a1[i];
    k=0;
}
a1[l] = '\0';
}

int main(){
    char s1[20]="helloiam";
    char s2[20]="hi";

    squeeze(s1,s2);
    printf("%s",s1);
}