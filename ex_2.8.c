#include <stdio.h>

unsigned int rightrot(unsigned int x,int n)
{
    unsigned int mask;
    unsigned int ybits;
    unsigned int temp;
    int a;
    if(n!=0){
    mask = ~(~0 << n);
    
    a=(sizeof(x)*8)-n;

    temp=x&(mask);
    temp=temp<<a;

    x = x >> n;
    x=x|temp;

    return x;}
    else
    return x;
}

int main()
{
    unsigned int x = 11;   
    int n = 2;

    unsigned int result = rightrot(x,n);

    printf("Result = %u\n", result);

    return 0;
}
