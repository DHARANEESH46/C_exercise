#include<stdio.h>

#define MAX 1000

int main(){
    char s1[MAX]="-a-b0-9-d"; // output: abcdefgz-9
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