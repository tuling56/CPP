//  [11/22/2013 jmy]
/*
 *	�Լ�����sprintf���������ĳ���
 */

#include<stdio.h>
#define MAX 30

int my_sprintf()
{
   char str[MAX];
   sprintf(str,"���:%s","����str");
   puts(str);
   return 0;
}