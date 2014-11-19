#include <Windows.h>
#include <iostream>
#include <vector>
#include <io.h>
#include "CreateDll.h" //不包含lib.h的话，需要把h文件内的函数原型声明添加进本程序

//#pragma comment(lib,"process.dll"); //静态调用

using namespace std;

void getFiles( string path, vector<string>& files );
typedef int(*lpRecognize)(const char * readFileName,const char * saveFileName);//声明所需函数的对应函数指针类型,参数与dll中的recognize函数的一致  

int main()  
{  
	char * filePath = "E:\\软件";  
	
	//显示调用dll
	HINSTANCE hDll;  
	hDll = LoadLibrary("CreateInvokeDll.dll");//读取dll文件  
	
	lpRecognize recogID;  
	if(hDll != NULL)  
	{  
		recogID = (lpRecognize)GetProcAddress(hDll,"recognize");  //获得指向函数的函数指针
		if(recogID == NULL)  
		{  
			FreeLibrary(hDll);  
			return -1;  
		}  
		vector<string> files;  
		////获取该路径下的所有文件  
		getFiles(filePath, files );  

		char str[30];  
		int size = files.size();  
		//调用dll中的接口  
		for(int i =0;i< size;i++) 
			recogID(files[i].c_str(),str); //调用dll中的函数  
	}  
	FreeLibrary(hDll);
	system("pause");
	return 0;  
}  

void getFiles( string path, vector<string>& files )
{
	//文件句柄
	long  hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之,如果不是,加入列表
			if((fileinfo.attrib &_A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}