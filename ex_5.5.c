#include<stdio.h>
#include<string.h>

char * strn_cpy(char des[],char src[],int n){   
    int l1=strlen(src);
    int l2=strlen(des);
    char * temp = des;
    for(int i=0;i<n;i++){
            *des=*src;
            src++;
            des++;
    }
    return temp;
    
}
char * strn_cat(char s[],char t[],int n){
    
    char * temp=s;
    int l1=strlen(s);
    s=s+l1;
    for(int i=0;i<n;i++){
        if(*t){
            *s=*t;
            s++;
            t++;
        }
        else    break;
    }
    *s='\0';
    return temp;
}

int strn_cmp(char s[],char t[],int n){
    int cmp=0;
    for(int i=0;i<n;i++){
        if(*s && *t){
            if(*s==*t){
                s++;
                t++;
            }
            else{
                cmp=*s-*t;
                return cmp;
            }
        }
        else    return cmp;
    }
    return cmp;
}
int main(){
    char s[]="d";
    char t[]="dhar";
    int n=5;
     
    int choice;
    printf("Enter choice:\n1.strncmp\n2.strcat\n3.strcpy\n");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            printf("\nstrncmp RESULT WITH INBUILT FN : %d\n\n",strncmp(s,t,n));
            printf("strncmp RESULT WITH OWN FUNCTION : %d\n\n",strncmp(s,t,n));
            break;
        case 2:
            printf("CONCATENATED STRING WITH OWN FUNCTION : %s\n\n",strn_cat(s,t,n));
            break;   
        case 3:
            printf("\nCOPIED STRING : %s\n\n",strn_cpy(s,t,n));
            break;  
    }

}