// pnt_add.c -- pointer addition
#include <stdio.h>
#define SIZE 4
int pnt_add(void)
{
    short index;
	short dates [SIZE];
    short * pti;
    double bills[SIZE];
    double * ptf;

    pti = dates;    // assign address of array to pointer
    ptf = bills;
    printf("%23s %10s\n", "short", "double");
    for (index = 0; index < SIZE; index ++)
        printf("pointers + %d: %10p %10p\n",index, pti + index, ptf + index);
  
    return 0;
}
