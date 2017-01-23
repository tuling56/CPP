#include <string>
#include <iostream>

using namespace std;

bool digitCheck(char*inputstr)
{
	for (char *p = inputstr; *p != '\0'; p++) //""都没有进入这个循环体
	{ 
		cout << "*p:" << *p << endl;
		if (!isdigit(*p)||*inputstr=='0'||isspace(*p))
			return false;
	}
	/*
	for (; *inputstr != '\0'; inputstr++)
	{
		cout << "*p:" << *inputstr << endl;
		if (!isdigit(*inputstr) || *inputstr == '0')
			return false;
	}
	*/
	printf("Second:%s is digit\n", inputstr);
	//cout << *inputstr << "is digit" << endl;
	return true;
}

bool parasvalid(char* height, char* width)
{
	/*
	if (height == NULL && width == NULL)
		return true;
	if (height == NULL || width == NULL)
		return false;
    */

	if (digitCheck(height) && digitCheck(width))
	{
		/*int h = atoi(height);
		int w = atoi(width);
		cout << "h:" << h << endl << "w:" << w << endl;
		*/
		return true;
	}

	return false;
}


//bool变量异或的测试
bool isdiff()
{
	bool b1 = "";  //空字符串
	bool b2 = false;
	if (b1^b2){
		cout << "相异" << endl;
		return true;
	}
	else{
		cout << "不相异(相同)" << endl;
		return false;
	}	
}

bool comNull()
{
	printf("%s\n", "");
	if (NULL<0){
		cout << "Null>0" << endl;
	}
	else{
		cout << "Null not>0" << endl;
	}

	return false;
}


//测试入口
int main_test_validparas()
{
	//isdiff();
	comNull();
	cin.get();
	return 0;

	char *parh = "12";  //其等效于NULL和0
	char *parw = "";
	
	printf("parh:%s\n", parh);
	printf("parw:%s\n", parw);
	if (isdigit(*parw)){
		printf("First:%s is digit\n",parw);
	}

	if (parasvalid(parh, parw))
		cout << "******* check sucess ********" << endl;
	else
		cout << "******* check fail ********" << endl;
	
	cin.get();
	return 0;
}


//******************解决方案部分************************************
/*
extern bool tonumber(char*);
bool argument_valid_check(char*inputstr);
bool check_paras(char*width, char*height)
{
   if (argument_valid_check(width)^argument_valid_check(height))
       return false;


	if (argument_valid_check(width)^argument_valid_check(height)) //相异为假
	{
		return false;
	}
	
	//下面的为真
	if (argument_valid_check(width)&argument_valid_check(height)) //同为空或者同不为空
	{
		if (tonumber(width)>0&&tonumber(height)>0)
		{
			return true;
		}
	}

	return false;
}
*/

/*
//重构argument_valid_check(),修改其返回值类型如下：
//空 ：0
//转化失败（非数字）：-1
//数字成功： 2

只有和等于0或者4的时候是检验合法
bool check_args(void* width,void* height)
{
	int check=argument_valid_check(width)+argument_valid_check(height);
	
	//当均为空的时候tonumber()返回值nil?
	//if(check==0||check==4)  //再检验数字是否都大于0
	//	return true;
	
	if(check==0)   return true;  //均为空，返回真

	if(check==4)
		if(tonumber(width)>0&&tonumber(height)>0)
			return true;            //均为数字，且大于0，返回真


	return false;
}
*/

/*
//不重构argument_valid_check(),只调用其返回数字为真的功能

bool check_args(void* width,void* height)
{

	if(width==NULL &&height==NULL)   //均为空，返回真
		return true;
	//if(argument_valid_check(width)&&argument_valid_check(height))//均是数字，再检验是否都大于0
	if(tonumber(width)>0&&tonumber(height)>0)
			return true;         //均为数字，且大于0，返回真

	return false;  //其它情况均为假
}
*/