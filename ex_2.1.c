#include <stdio.h>
#include <limits.h>
#include <float.h>


int main()
{
    printf("RANGES USING STANDARD HEADERS\n\n");

    printf("signed char   : %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char : 0 to %u\n\n", UCHAR_MAX);

    printf("signed short   : %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short : 0 to %u\n\n", USHRT_MAX);

    printf("signed int   : %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int : 0 to %u\n\n", UINT_MAX);

    printf("signed long   : %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long : 0 to %lu\n\n", ULONG_MAX);

    printf("float       : %e to %e\n", FLT_MIN, FLT_MAX);
    printf("double      : %e to %e\n", DBL_MIN, DBL_MAX);
    printf("long double : %Le to %Le\n\n", LDBL_MIN, LDBL_MAX);

    printf("RANGES BY DIRECT COMPUTATION\n\n");

    unsigned char uc = 0;
    unsigned char uc_max = 0;

    do {
        uc_max = uc;
        uc++;
    } while (uc != 0);

    printf("unsigned char : 0 to %u\n", uc_max);

    signed char sc = 0;
    signed char sc_max = 0, sc_min = 0;

    while (sc >= 0) {
        sc_max = sc;
        sc++;
    }

    sc = 0;
    while (sc <= 0) {
        sc_min = sc;
        sc--;
    }

    printf("signed char   : %d to %d\n", sc_min, sc_max);

    return 0;
}
