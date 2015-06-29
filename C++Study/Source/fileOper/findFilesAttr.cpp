/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	findFilesAttr.cpp
* Brief: ��ȡ�����ļ���������
* Source:
* Status: û�е�ͨ
* Date:	[1/30/2015 jmy]
************************************************************************/
#include <io.h>  //_finddata_�������ļ�
#include <iostream>  
#include <string>  

using namespace std;  
  
void findFileAttr(string path)  
{  
    _finddata_t file;  
    long longf;  
  
    //_findfirst���ص���long��; long __cdecl _findfirst(const char *, struct _finddata_t *)  
    if((longf = _findfirst(path.c_str(), &file))==-1l) {  
        cout<<"�ļ�û���ҵ�!/n";  
    }  
    else  
    {  
        cout<<"/n�ļ��б�:/n";  
        //int __cdecl _findnext(long, struct _finddata_t *);����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1  
        string tempName;  
        while( _findnext( longf, &file ) == 0 )  
        {  
            tempName = "";  
            tempName = file.name;  
            if (tempName == "..") {  
                continue;  
            }  
            cout<<file.name;  
			//�ļ������ж�
            if(file.attrib == _A_NORMAL) {  
                cout<<" ��ͨ�ļ� ";  
            }  
            else if(file.attrib == _A_RDONLY) {  
                cout<<"  ֻ���ļ�  ";  
            }  
            else if(file.attrib == _A_HIDDEN ){  
                cout<<"  �����ļ�  ";  
            }  
            else if(file.attrib == _A_SYSTEM ){  
                cout<<"  ϵͳ�ļ�  ";  
            }  
            else if(file.attrib == _A_SUBDIR) {  
                cout<<"  ��Ŀ¼  ";  
            }  
            else {  
                cout<<"  �浵�ļ�  ";  
            }  

            cout<<endl;  
        }  
    }  
  
    _findclose(longf);  
  
}  

//���ܲ�����
//int main()
//{
//	//Mat src = imread("");
//
//	findFileAttr("E:\\360YPan\\Git\\C++_Github\\C++Study\\Source\\fileOpera");
//    cin.get();
//	return 0;
//}