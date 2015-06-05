#include <Windows.h>
#include <iostream>
#include <vector>
#include <io.h>

using namespace std;

void getFiles( string path, vector<string>& files );
typedef int(*lpRecognize)(const char * readFileName,const char * saveFileName);//参数与dll中的recognize函数的一致  

int main()  
{  
	HINSTANCE hDll;  

	char * filePath = "D:\\sample";  
	lpRecognize recogID;  
	hDll = LoadLibrary("..\\debug\\C++编译生成DLL及调用.dll");//读取dll文件  

	if(hDll != NULL)  
	{  
		recogID = (lpRecognize)GetProcAddress(hDll,"recognize");  
		if(recogID == NULL)  
		{  
			FreeLibrary(hDll);  
			return -1;  
		}  

		vector<string> files;  
		////获取该路径下的所有文件  
		getFiles(filePath, files );  
		char str[30];  
		//调用dll中的接口  
		for (int i = 0; i< files.size(); i++)
			recogID(files[i].c_str(),str); //调用dll中的函数  
	}  
	getchar();
	FreeLibrary(hDll);  
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