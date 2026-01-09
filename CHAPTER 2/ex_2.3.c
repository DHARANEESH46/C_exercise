/*Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F.*/

#include <stdio.h>
#include <string.h>

int htoi(const char s[]) {
    int i = 0;
    int value = 0;
    char c;
    int a=strlen(s)-1;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')){
        i = 2;
        a=a-2;
    }

    while ((c = s[i]) != '\0') {
        if (c >= '0' && c <= '9')       
            value = value * 16 + (c-'0');
        else if (c >= 'a' && c <= 'f')  
            value = value * 16 + (c-'a'+10);
        else if (c >= 'A' && c <= 'F')    
            value = value * 16 + (c-'A'+10);
        a--;
        i++;
    }

    return value;
}

int main() {
    char hex1[] = "576a";
    char hex2[] = "21474836";

    printf("%s,%d\n", hex1, htoi(hex1));
    printf("%s,%d\n", hex2, htoi(hex2));

    return 0;
}
