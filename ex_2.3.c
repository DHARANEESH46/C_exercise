#include <stdio.h>
#include <string.h>

int power(int x,int y){
    int ans=1;
    for (int i=0;i<y;i++){
        ans*=x;
    }
    return ans;
}
int htoi(const char s[]) {
    int i = 0;
    int value = 0;
    char c;
    int a=strlen(s)-1;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
        a=a-2;

    while ((c = s[i]) != '\0') {
        if (c >= '0' && c <= '9')       
            value += (c - '0')*power(16,a);
        else if (c >= 'a' && c <= 'f')  
            value += (c - 'a'+10)*power(16,a);
        else if (c >= 'A' && c <= 'F')    
            value += (c - 'A'+10)*power(16,a);
        a--;
        i++;
    }

    return value;
}

int main() {
    char hex1[] = "0x1A3F";
    char hex2[] = "2b5";
    char hex3[] = "0Xff";

    printf("%s,%d\n", hex1, htoi(hex1));
    printf("%s,%d\n", hex2, htoi(hex2));
    printf("%s,%d\n", hex3, htoi(hex3));

    return 0;
}
