/*Write a program to copy its input to its output, replacing each string of one or
more blanks by a single blank.*/

#include<stdio.h>

int main(){
    int c;
    int blank=0;

    while((c=getchar())!=EOF){
        if (c==' ' || c=='\t'){
            if(blank==0){
                putchar(' ');
                blank=1;
            }
        }
        else{
            putchar(c);
            blank=0;
        }
    }
}