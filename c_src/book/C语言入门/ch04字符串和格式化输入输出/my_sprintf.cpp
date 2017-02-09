//  [11/22/2013 jmy]
/*
 *	自己测试sprintf（）函数的程序
 */

#include<stdio.h>
#define MAX 30

int my_sprintf()
{
   char str[MAX];
   sprintf(str,"你好:%s","我是str");
   puts(str);
   return 0;
}