#include <string>
#include <iostream>

using namespace std;

bool digitCheck(char*inputstr)
{
	for (char *p = inputstr; *p != '\0'; p++) //""��û�н������ѭ����
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


//bool�������Ĳ���
bool isdiff()
{
	bool b1 = "";  //���ַ���
	bool b2 = false;
	if (b1^b2){
		cout << "����" << endl;
		return true;
	}
	else{
		cout << "������(��ͬ)" << endl;
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


//�������
int main_test_validparas()
{
	//isdiff();
	comNull();
	cin.get();
	return 0;

	char *parh = "12";  //���Ч��NULL��0
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


//******************�����������************************************
/*
extern bool tonumber(char*);
bool argument_valid_check(char*inputstr);
bool check_paras(char*width, char*height)
{
   if (argument_valid_check(width)^argument_valid_check(height))
       return false;


	if (argument_valid_check(width)^argument_valid_check(height)) //����Ϊ��
	{
		return false;
	}
	
	//�����Ϊ��
	if (argument_valid_check(width)&argument_valid_check(height)) //ͬΪ�ջ���ͬ��Ϊ��
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
//�ع�argument_valid_check(),�޸��䷵��ֵ�������£�
//�� ��0
//ת��ʧ�ܣ������֣���-1
//���ֳɹ��� 2

ֻ�к͵���0����4��ʱ���Ǽ���Ϸ�
bool check_args(void* width,void* height)
{
	int check=argument_valid_check(width)+argument_valid_check(height);
	
	//����Ϊ�յ�ʱ��tonumber()����ֵnil?
	//if(check==0||check==4)  //�ټ��������Ƿ񶼴���0
	//	return true;
	
	if(check==0)   return true;  //��Ϊ�գ�������

	if(check==4)
		if(tonumber(width)>0&&tonumber(height)>0)
			return true;            //��Ϊ���֣��Ҵ���0��������


	return false;
}
*/

/*
//���ع�argument_valid_check(),ֻ�����䷵������Ϊ��Ĺ���

bool check_args(void* width,void* height)
{

	if(width==NULL &&height==NULL)   //��Ϊ�գ�������
		return true;
	//if(argument_valid_check(width)&&argument_valid_check(height))//�������֣��ټ����Ƿ񶼴���0
	if(tonumber(width)>0&&tonumber(height)>0)
			return true;         //��Ϊ���֣��Ҵ���0��������

	return false;  //���������Ϊ��
}
*/