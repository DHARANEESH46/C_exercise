/*In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x. Explain why. Use this observation to write a faster version of bitcount.*/

#include<stdio.h>

int main(){
    unsigned int x=15;
    int res=0;

    while(x!=0){
        res++;
        x=x&(x-1);
    }
    printf("%d",res);
}