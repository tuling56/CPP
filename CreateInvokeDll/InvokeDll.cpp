#include <Windows.h>
#include <iostream>
#include <vector>
#include <io.h>
#include "CreateDll.h" //������lib.h�Ļ�����Ҫ��h�ļ��ڵĺ���ԭ��������ӽ�������

//#pragma comment(lib,"process.dll"); //��̬����

using namespace std;

void getFiles( string path, vector<string>& files );
typedef int(*lpRecognize)(const char * readFileName,const char * saveFileName);//�������躯���Ķ�Ӧ����ָ������,������dll�е�recognize������һ��  

int main()  
{  
	char * filePath = "E:\\���";  
	
	//��ʾ����dll
	HINSTANCE hDll;  
	hDll = LoadLibrary("CreateInvokeDll.dll");//��ȡdll�ļ�  
	
	lpRecognize recogID;  
	if(hDll != NULL)  
	{  
		recogID = (lpRecognize)GetProcAddress(hDll,"recognize");  //���ָ�����ĺ���ָ��
		if(recogID == NULL)  
		{  
			FreeLibrary(hDll);  
			return -1;  
		}  
		vector<string> files;  
		////��ȡ��·���µ������ļ�  
		getFiles(filePath, files );  

		char str[30];  
		int size = files.size();  
		//����dll�еĽӿ�  
		for(int i =0;i< size;i++) 
			recogID(files[i].c_str(),str); //����dll�еĺ���  
	}  
	FreeLibrary(hDll);
	system("pause");
	return 0;  
}  

void getFiles( string path, vector<string>& files )
{
	//�ļ����
	long  hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//�����Ŀ¼,����֮,�������,�����б�
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