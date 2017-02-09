#include <iostream>
#include <string>

using namespace std;

/*
 *	功能：对字符串进行遍历判断
 *  输入：
 *  输出：
 *  状态：
 */
int modeordigit(string result)
{	
	int charNum=0,digitNum=0;
	for (int i=0;i<result.size();i++)
	{
		if (isspace(result[i]))
			continue;
		if (isalpha(result[i])) //必须全部是字符才是模式
			charNum++;
		else if (isdigit(result[i]))
			digitNum++;
	}
	if (charNum==result.size())
	     return 1;//mode
	else if (digitNum==result.size())
	     return 0;  //digit
	else{
		printf("some unknown control character\n"); 
		return -1; 
	}
}


int ssubstr(string result)
{
	string ocr=result.substr(0,result.length()-2);
	cout<<"OCR:"<<ocr<<endl;
	return 0;
}

/*
 *	功能：字符转化为整数
 *  输入：十进制字符串
 *  输出：字符串对应的整数
 *  状态：
 */

int m_stoi(string str)
{
	string restult;
	//先判断字符中是否有空格，若有，则去除
	for(int i=0;i<str.length();i++)
	{
		if (isdigit(str[i]))
		{
			//restult[i]=str[i];
			restult+=str[i];
		}
		else
		{
			cout<<"error convert"<<endl;
			return -1;
		}
	}
	cout<<"转化后的字符串"<<restult<<endl;
	cout<<"转化后数字是"<<stoi(restult)<<stoi("123 45")<<endl;


	return stoi(restult);
}




//功能测试区
//int main(int argc, char const *argv[])
//{
//	string result="123 45";
//	//int c=modeordigit(result);
//	cout<<m_stoi(result)<<endl;
//	
//	cin.get();
//	return 0;
//}