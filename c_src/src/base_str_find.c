/*
 * 功能：基本字符串查找
 * 参考：http://blog.csdn.net/feixiaoxing/article/details/6908453
 * 状态：开发中...
 */ 

#include<stdio.h>
#include<string.h>


//判断search字符串是否包含在str字符串中
char *base_str_find(const char*str,char*search)
{

    if(NULL==str||search==str)
        return NULL;

    int slen=strlen(search);
    
    int index=0;
    while(*str && (int)strlen(str)>slen) //未结束且余下的字符串的长度大于搜索字符串的长度
    {
        for(;index<slen;index++)
        {
            if(str[index]!=search[index])
                break;
        }

        if(index==slen)
            return (char*) str;

        str++;
    }

    return NULL;
}


int main()
{
    const char *str="zhangwanglizhao";
    char *search="li";
    char * res=base_str_find(str,search);
    if(NULL!=res)
        printf("找到的结果如下:%s\n",res);
    else
        printf("没有查找到");
    return 0;

}
