#include <string>
#include <iostream> //��׼���������
#include <fstream>  //�ļ����������

using std::string;
using namespace std;

int my_string()
{
	/*string s1,s2,s3;
	cin>>s1>>s2;
	cout<<s1<<s2<<endl;


	while(cin>>s3)
	{
		cout<<s3<<endl;
	}
*/
	//�ļ�����
	string sfile;
	char*filename="cplusplus.txt";
	fstream fstrm(filename);
	if (!fstrm)
	{
		cout<<"fail open"<<endl;
	}
	while (cin>>sfile)
	{
		fstrm<<sfile;
		if (getchar()=='e')
		{
			break;
		}
	}
	
	fstrm.close();

	cin.get();
	return 0;
}