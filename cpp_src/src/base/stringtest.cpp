#include <iostream>
#include <string>

using namespace std;

/*
 *	���ܣ����ַ������б����ж�
 *  ���룺
 *  �����
 *  ״̬��
 */
int modeordigit(string result)
{	
	int charNum=0,digitNum=0;
	for (int i=0;i<result.size();i++)
	{
		if (isspace(result[i]))
			continue;
		if (isalpha(result[i])) //����ȫ�����ַ�����ģʽ
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
 *	���ܣ��ַ�ת��Ϊ����
 *  ���룺ʮ�����ַ���
 *  ������ַ�����Ӧ������
 *  ״̬��
 */

int m_stoi(string str)
{
	string restult;
	//���ж��ַ����Ƿ��пո����У���ȥ��
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
	cout<<"ת������ַ���"<<restult<<endl;
	cout<<"ת����������"<<stoi(restult)<<stoi("123 45")<<endl;


	return stoi(restult);
}




//���ܲ�����
//int main(int argc, char const *argv[])
//{
//	string result="123 45";
//	//int c=modeordigit(result);
//	cout<<m_stoi(result)<<endl;
//	
//	cin.get();
//	return 0;
//}