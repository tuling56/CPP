#include <string>
#include <iostream>

using namespace std;


//�ж��Ƿ��ǻ����ַ���
int judge_if(string input)
{
	int j = input.length()-1;
	for (int i = 0; i < input.length();i++)
	{
		for (;j > i; j--)
		{
			//cout << input[i] << " PK " << input[j] << endl;
			if (input[i]==input[j]){
				j--;
				break;
			}
			else{
				//cout << input[i] << "!=" << input[j] << endl;
				return 0;
			}
		}
	}
	return 1;
}

//�ж��ܷ����һ���ַ����ɻ����ַ���
//���ִ�Сд��Ĭ��ȫ����Сд��
int judge_insert_if(string input)
{
	for (int i = 0; i < input.length();i++)
	{
		for (char c = 'a'; c <='z';c++)
		{
			string teststr = input;
			teststr.insert(i, 1, c);
			int jd = judge_if(teststr);
			if (jd == 0)
				continue;
			else
				return 1;
		}
	}
	return 0;
}


//�������
//int main()
//{
//	int res = judge_insert_if("htcathe");
//	if (res==0){
//		cout << "no roll back" << endl;
//	}
//	else{
//		cout << "roll back" << endl;
//	}
//
//	cin.get();
//	return 0;
//}