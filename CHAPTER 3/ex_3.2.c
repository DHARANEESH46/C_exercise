/*Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters.*/

#include <stdio.h>

int main() {
    int c;
    char ans[1000];
    int i=0;

    while ((c = getchar()) != EOF) {
        switch(c){
            case '\n':
                ans[i++]='\\';
                ans[i++]='n';
                break;
            case '\t':
                ans[i++]='\\';
                ans[i++]='t';
                break;
            default:
                ans[i++]=c;
    }

}
    printf("\n%s",ans);
}
