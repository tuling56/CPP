//实现字符串查找和确定位置的函数
#include <stdio.h>
#include <string.h>

int VioMatch(char*,char*);
int ViolentMatch(char*,char*);

int main(int argc, char *argv[])
{
	printf("find search_str in text_str:\n");
	char*text="niwhaowod e de";
	char*search="wod";
	
	//VioMatch(text,search);
	ViolentMatch(text,search);

	getchar();
	
	return 0;
}

//（1）字符串查找和匹配算法，返回匹配字符串的位置
//解法1：暴力匹配算法

int VioMatch(char*text,char*search)
{
	char*text_backup=text;
	char*search_backup=search;

	int locate=1;
	int matchlen=0;
	while(*search!='\0')
	{
		while(*text!='\0')
		{
			char t1=*search;
			char t2=*text;
			if(t1!=t2){
			//if(*search!=*text){
				matchlen=0;        //不匹配就重新计数
				locate++;          //不匹配，位置就后移
			}
			else{
				matchlen++;
				break;
			}
			text++; 
		}
		search++;
	}

	if (matchlen==strlen(search)){
		printf("find {%s} in {%s} at %d\n", search_backup,text_backup,locate);
	}
	else{
		printf("no find\n");
	}
	
	return locate;
}

//（2）来自 http://blog.csdn.net/v_july_v/article/details/7041827 暴力匹配算法
// 假设现在文本串匹配到i位置，模式串匹配到j位置

int ViolentMatch(char*s,char*p)
{
	int slen=strlen(s);
	int plen=strlen(p);

	int i=0;
	int j=0;

	while(i<slen&&j<plen)
	{
		if (s[i]==p[j])
		{
			i++;
			j++;
		}
		else
		{
			i=i-(j-1); //没有匹配成功，i回退
			j=0;
		}
	}

	if (j==plen){
		printf("success in %d\n",i-j); //注意返回的是位置代表的意义
		return i-j;
	}
	else
		return -1;
}

