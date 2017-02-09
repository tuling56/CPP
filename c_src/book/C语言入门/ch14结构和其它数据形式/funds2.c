/* funds2.c -- passing a pointer to a structure */
#include <stdio.h>
#define FUNDLEN 50

struct funds {
    char   bank[FUNDLEN];
    double bankfund;
    char   save[FUNDLEN];
    double savefund;
};

double sum1(const struct funds *);  /* argument is a pointer */

int fund2(void)
{
    struct funds stan = {
        "Garlic-Melon Bank",
        3024.72,
        "Lucky's Savings and Loan",
        9237.11
    };
    printf("Stan has a total of $%.2f.\n", sum1(&stan));
    
    return 0;
}

double sum1(const struct funds * money)
{
    return(money->bankfund + money->savefund);
}
