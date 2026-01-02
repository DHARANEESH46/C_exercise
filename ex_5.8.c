#include<stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 1){
        printf("invalid year");
        return -1;}

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (month < 1 || month > 12){
        printf("invalid month");
        return -1;}

    if (day < 1 || day > daytab[leap][month]){
        printf("invalid day");
        return -1;}

    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap, maxday;

    if (pmonth == NULL || pday == NULL){
        printf("invalid pointer location");
        return -1;}

    if (year < 1){
        printf("invalid year");
        return -1;}

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    maxday = leap ? 366 : 365;

    if (yearday < 1 || yearday > maxday){
        printf("invalid yearday");
        return -1;}

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;

    return 1;
}

char *month_name(int n)
{
    static char *name[] = {"Illegal month","January", "February", "March","April", "May", "June",
                            "July", "August", "September","October", "November", "December"};
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(){
    int year=2026;
    int month=3;
    int day=1;
    int yearday=121;
    int pmonth,pday;

    int ans_day=day_of_year(year,month,day);

    ans_day<=0?:printf("\n%d\n",ans_day);
    
    int ans_mon=month_day(year,yearday,&pmonth,&pday);

    ans_mon<=0?:printf("%s %d\n",month_name(pmonth),pday);


    
}
