#include<stdio.h>
#include<ctype.h>
#include<string.h>

int _atoi(char*s)   //completed
{
    int n, sign;
    
    while(isspace(*s))  s++;
    
    sign = (*s == '-') ? -1 : 1;
    
    if (*s == '+' || *s == '-')
        s++;
    
        for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
  
    return sign * n;
}

int htoi(char s[]) {    //completed
    int i = 0;
    int value = 0;
    char c;
    int a=strlen(s)-1;

    if (*s++ == '0' && ( *s == 'x' || *s == 'X')){
        i = 2;
        a=a-2;
        s++;
    }
    else    s--;

    while (*s != '\0') {
        if (*s >= '0' && *s <= '9')       
            value = value * 16 + (*s-'0');
        else if (*s >= 'a' && *s <= 'f')  
            value = value * 16 + (*s-'a'+10);
        else if (*s >= 'A' && *s <= 'F')    
            value = value * 16 + (*s-'A'+10);
        a--;
        i++;
        s++;
    }

    return value;
}

void reverse(char s[]){         //completed
    char *p =s;
    for (; *s != '\0'; s++);
    s--;
    while(p<s){
        char temp=*s;
        *s=*p;
        *p=temp;
        s--;
        p++;
    }
}

void itoa(int n, char s[])      //completed
{
    int i = 0;
    int sign = n;
    char *t=s;

    do {
        int digit = n % 10;
        if (digit < 0)
            digit = -digit;

        *s = digit + '0';
        s++;
        n /= 10;
    } while (n != 0);

    if (sign < 0)
        *s = '-';
        s++;

    *s = '\0';
    reverse(t);
}

void itob(int n,char s[],int b,int w){      //completed
    int sign = n;
    int i=0,rem=0;
    char *tem=s;

    if(n!=0 && b>=2 && b<=36){
    while(n!=0){
        rem=n%b;
        n=n/b;
        if (rem<0){
            rem=-rem;
        }   
        if(rem<=9){
            *s++=rem+'0';
        }
        else{
            *s++='A'+rem-10;
        }
    }
    if(sign<0)
        *s++='-';
    if((i=s-tem)<w){
        for(int j=i;j<w;j++)
            *s++=' ';
    }
    *s++='\0';

    reverse(tem);
}
    else{
        if(n==0){
            *s++='0';
            *s='\0';
        }
        else{
            printf("invalid base\n");
        }
    }
}

int strindex(char *s, char *t)          //completed
{
    char *ps, *pt, *start;
    int pos = -1;
    int index = 0;

    for (ps = s; *ps != '\0'; ps++, index++) {
        start = ps;
        pt = t;

        while (*start == *pt && *pt != '\0') {
            start++;
            pt++;
        }

        if (*pt == '\0')        
            pos = index;      
    }

    return pos;
}

int main()
{
    char s[] = "aba";
    char t[] = "ab";

    printf("%d\n", strindex(s, t));
    return 0;
}
