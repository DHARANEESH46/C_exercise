/*Revise minprintf to handle more of the other facilities of printf.*/

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int ival;
    unsigned uval;
    double dval;
    char *sval;
    void *pval;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {

        case 'd':   
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;

        case 'o':  
            uval = va_arg(ap, unsigned);
            printf("%o", uval);
            break;

        case 'x':   
            uval = va_arg(ap, unsigned);
            printf("%x", uval);
            break;

        case 'X':   
            uval = va_arg(ap, unsigned);
            printf("%X", uval);
            break;

        case 'u':  
            uval = va_arg(ap, unsigned);
            printf("%u", uval);
            break;

        case 'c':   
            ival = va_arg(ap, int);   
            putchar(ival);
            break;

        case 'e':   
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;

        case 'E':
            dval = va_arg(ap, double);
            printf("%E", dval);
            break;

        case 'f':   
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;

        case 'g':   
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;

        case 'G':
            dval = va_arg(ap, double);
            printf("%G", dval);
            break;

        case 'p':   
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;

        case 's':   
            sval = va_arg(ap, char *);
            printf("%s", sval);
            break;

        case '%':   
            putchar('%');
            break;

        default:    
            putchar(*p);
            break;
        }
    }

    va_end(ap);
}


int main()
{
    minprintf("Int: %d\n", 123);
    minprintf("Float: %f\n", 3.14159);
    minprintf("Hex: %x\n", 255);
    minprintf("String: %s\n", "hello");
    minprintf("Char: %c\n", 'A');
    return 0;
}

