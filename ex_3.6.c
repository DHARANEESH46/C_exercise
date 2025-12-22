#include<stdio.h>

void reverse(char s[]){
    int len=0;
    int start=0;

    for (len = 0; s[len] != '\0'; len++);
    len--;
    while(start<len){
        char temp=s[start];
        s[start]=s[len];
        s[len]=temp;
        start++;
        len--;
    }
}

void itob(int n,char s[],int b,int w){
    int sign = n;
    int i=0,rem=0;

    
    if(n!=0 && b>=2 && b<=36){
    while(n!=0){
        rem=n%b;
        n=n/b;
        if (rem<0){
            rem=-rem;
        }   
        if(rem<=9){
            s[i++]=rem+'0';
        }
        else{
            s[i++]='A'+rem-10;
        }
    }
    if(sign<0)
        s[i++]='-';
    if(i<w){
        for(int j=i;j<w;j++)
            s[i++]=' ';
    }
    s[i++]='\0';

    reverse(s);
}
    else{
        if(n==0){
            s[0]='0';
            s[1]='\0';
        }
        else{
            printf("invalid base\n");
        }
    }
}

int main(){
    int n=-10;
    int b=16;
    char s[1000];
    int width = 5;


    itob(n,s,b,width);
    if(b>=2 && b<=36)
    printf("the result is : %s\n",s);
}