/*Write the function any(s1,s2), which returns the first location in a string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.*/

#include<stdio.h>

int any(char a1[], char a2[])
{
int i, j,ans=-1;
for (i = 0; a1[i] != '\0'; i++){
    for(j=0;a2[j]!='\0';j++){
        if (a1[i]==a2[j]){
            ans=i;
            break;
        }
    }
    if(ans!=-1)
        break;
}
return ans;
}
int main(){
    char s1[20]="healloiam";
    char s2[20]="am";

    printf("%d",any(s1,s2));
}