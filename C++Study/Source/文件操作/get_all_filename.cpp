/* �ο����ӣ�
 *1��http://qiaoxinwang.blog.163.com/blog/static/86096452010612139172/
 *2��http://blog.csdn.net/cxf7394373/article/details/7195661
 *	
 */

#include <string>
#include <vector>
#include <iostream>
#include <io.h>

using namespace std;

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


int my_getfiles()
{
	char * filePath = "C:\\Users\\jmy\\Desktop\\OCR\\test";  
	vector<string> files;  

	////��ȡ��·���µ������ļ�  
	getFiles(filePath, files );  

	char str[30];  
	int size = files.size();  
	for (int i = 0;i < size;i++)  
	{  
		cout<<files[i].c_str()<<endl;  

	} 

	return 0;
}