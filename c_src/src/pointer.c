#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int * getpin()
{
    static int a=10;
    int *pin;
    pin=&a;

    return pin;
}


void basestr()
{
    char * bs="firstline\nsecondline";
    printf("字符串长度:%d\n",strlen(bs));
    bs=bs+1;
    printf("后移一位后字符串长度是:%d\n",strlen(bs));
    printf("后移一位后的字符串是:%s\n",bs);

}

int main()
{

    basestr();
    return 0;

    int *pout;
    pout=getpin();
    printf("返回的变量是：%d\n",*pout);

    return 0;

}

