/*Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.*/

#include<stdio.h>
#include<string.h>
#define MAX 1000

int main(){
    char s1[MAX]="-ab-f0-42-u"; 
    char s2[MAX];

    int n=strlen(s1);
    int k=0;
    
    for(int i=0;i<n;i++){
        if(s1[i]!='-'){
            s2[k++]=s1[i];
        }
        else{
            if(i==0 || i==n-1){
                s2[k++]=s1[i];
            }
            else{
                if((s1[i-1]>='a' && s1[i+1]<='z') && s1[i-1]<=s1[i+1]){
                    for(int j=s1[i-1]+1;j<s1[i+1];j++){
                        s2[k++]=j;
                    }
                }
                else if((s1[i-1]>='A' && s1[i+1]<='Z') && s1[i-1]<=s1[i+1]){
                    for(int j=s1[i-1]+1;j<s1[i+1];j++){
                        s2[k++]=j;
                    }
                }
                else if((s1[i-1]>='0' && s1[i+1]<='9') && s1[i-1]<=s1[i+1]){
                    for(int j=s1[i-1]+1;j<s1[i+1];j++){
                        s2[k++]=j;
                    }
                }
                else{
                    s2[k++]=s1[i];
                }
            }
        }

    }
    s2[k]='\0';
    printf("%s\n",s2);

}