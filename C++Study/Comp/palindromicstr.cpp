#include <string>
#include <iostream>

using namespace std;


//判断是否是回文字符串
int judge_if(string input)
{
	int j = input.length()-1;
	for (int i = 0; i < input.length();i++)
	{
		for (;j > i; j--)
		{
			cout << input[i] << " PK " << input[j] << endl;
			if (input[i]==input[j]){
				j--;
				break;
			}
			else{
				cout << input[i] << "!=" << input[j] << endl;
				return 0;
			}
		}
	}
	return 1;
}


int main()
{
	int res = judge_if("htcath");
	if (res==0){
		cout << "no roll back" << endl;
	}
	else{
		cout << "roll back" << endl;
	}

	cin.get();
	return 0;
}