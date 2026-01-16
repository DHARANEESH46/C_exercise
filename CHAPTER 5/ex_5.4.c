/*Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.*/

#include<stdio.h>
#include<string.h>

int str_end(char *s,char *t){
    int l1=strlen(s);
    int l2=strlen(t);

    if(l1>l2){
        s=s+l1-l2;
        while(*s!=0){
            if(*s==*t){
                s++;
                t++;
            }
            else    return 0;
        }
    }
    else{
        return 0;
    }
    return 1;


}
int main(){
    char s[100]="hello";
    char t[100]="a";

    printf("%d",str_end(s,t));
}