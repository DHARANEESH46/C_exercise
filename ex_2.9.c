#include<stdio.h>

int main(){
    unsigned int x=2234423;
    int res=0;

    while(x!=0){
        res++;
        x=x&(x-1);
    }
    printf("%d",res);
}