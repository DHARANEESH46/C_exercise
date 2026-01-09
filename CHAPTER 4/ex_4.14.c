/*Define a macro swap(t,x,y) that interchanges two arguments of type t.(Block structure will help.)*/

#include <stdio.h>

#define swap(t, x, y) \
        t temp = x;   \
        x = y;        \
        y = temp;     \

int main()
{
    int a = 5, b = 10;
    
    printf("a = %d, b = %d\n", a, b);

   
    swap(int, a, b);
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
