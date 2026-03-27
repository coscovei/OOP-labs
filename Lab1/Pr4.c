#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int year = 0;
    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid input, the year should be greater or equal to 1876\n");
        exit(1);
    }
    while (year < 1876) {
        printf("Invalid input, the year should be greater or equal to 1876\n");
        printf("Enter year: ");
        scanf("%d", &year);
    }

    int A = year%19;
    int B = year%4;
    int C = year%7;
    int D = (19*A+24)%30;
    int E = (2*B+4*C+6*D+5)%7;
    int Day = 22+E+D;

    struct Easter_Date {
        int year;
        char month[5];
        int day;
    };

    struct Easter_Date EasterDate;
    EasterDate.year = year;
    if (Day>31) {
        strcpy(EasterDate.month, "April");
        EasterDate.day = Day-31;
    }
    else {
        strcpy(EasterDate.month ,"March");
        EasterDate.day = Day;
    }
    printf("In year %d the Easter date is %02d %s\n", EasterDate.year, EasterDate.day, EasterDate.month);

}
