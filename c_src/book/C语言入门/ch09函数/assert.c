/* assert.c -- use assert() */

#include <stdio.h>
#include <math.h>
// #define NDEBUG  //��������assert.h�������ǰ�棬���ؿ���assert�����Ƿ������á�
#include <assert.h>

int my_assert(void)
{
    double x, y, z;
    
    puts("Enter a pair of numbers (0 0 to quit): ");
    while (scanf("%lf %lf", &x, &y) == 2 && (x != 0 || y != 0))
    {
        z = x * x - y * y;  /* should be + */
        assert(z >= 0);
        printf("answer is %f\n", sqrt(z));
        puts("Next pair of numbers: ");
    }
    puts("Done");
    
    return 0;
}
