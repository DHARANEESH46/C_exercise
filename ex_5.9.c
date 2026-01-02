#include<stdio.h>

static char daytab0[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char daytab1[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static char *daytab[2] = { daytab0, daytab1 };

int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *p;

    if (year < 1){
        printf("invalid year\n");
        return -1;}

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (month < 1 || month > 12){
        printf("invalid month\n");
        return -1;}

    if (day < 1 || day > daytab[leap][month]){
        printf("invalid day\n");
        return -1;}

    p = daytab[leap] + 1;

    while (--month > 0)
        day += *p++;

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap, maxday;
    char *p;

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

    p = daytab[leap] + 1;

    for (*pmonth = 1; yearday > *p; (*pmonth)++) {
        yearday -= *p;
        p++;
    }

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
    int month=12;
    int day=31;
    int yearday=364;
    int pmonth,pday;

    int ans_day=day_of_year(year,month,day);

    ans_day<=0?:printf("\n%d\n",ans_day);
    
    int ans_mon=month_day(year,yearday,&pmonth,&pday);

    ans_mon<=0?:printf("%s %d\n",month_name(pmonth),pday);


    
}
