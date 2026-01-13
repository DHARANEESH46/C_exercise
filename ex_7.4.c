/*Write a private version of scanf analogous to minprintf from the previous
section.*/

#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {

        if (*p != '%')
            continue;

        switch (*++p) {

        case 'd':       
        case 'i':
            scanf("%d", va_arg(ap, int *));
            break;

        case 'u':      
            scanf("%u", va_arg(ap, unsigned int *));
            break;

        case 'f':      
        case 'e':
        case 'g':
            scanf("%lf", va_arg(ap, double *));
            break;

        case 'x':      
            scanf("%x",va_arg(ap, unsigned int *));
            break;

        case 'o':       
            scanf("%o", va_arg(ap, unsigned int *));
            break;

        case 'c':       
            scanf(" %c", va_arg(ap, char *));    
            break;

        case 's':       
            scanf("%s", va_arg(ap, char *));
            break;

        default:
            break;
        }
    }

    va_end(ap);
}


int main(void)
{
    int i;
    unsigned u, hx, oc;
    double f;
    char s[50];
    char c;

    printf("Enter: int unsigned hex octal double string char\n");

    minscanf("%d %u %x %o %f %s %c",
             &i, &u, &hx, &oc, &f, s, &c);

    printf("\nValues:\n");
    printf("int      = %d\n", i);
    printf("unsigned = %u\n", u);
    printf("hex      = %x\n", hx);
    printf("octal    = %o\n", oc);
    printf("double   = %f\n", f);
    printf("string   = %s\n", s);
    printf("char     = %c\n", c);

    return 0;
}
