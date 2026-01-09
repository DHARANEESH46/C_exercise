/*Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop*/

#include <stdio.h>

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;

        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (low < n && v[low] == x)
        return low;

    return -1;
}

int main(void)
{
    int v[] = {2, 5, 7, 10, 14, 18, 21};
    int n = sizeof(v) / sizeof(v[0]);
    int x=10;
    int pos;

    pos = binsearch(x, v, n);

    if (pos != -1)
        printf("Element %d found at index %d\n", x, pos);
    else
        printf("Element %d not found\n", x);

    return 0;
}
