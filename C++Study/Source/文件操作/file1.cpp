#include <string>
#include <iostream> //标准输入输出流
#include <fstream>  //文件输入输出流

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
	//文件操作
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