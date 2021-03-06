/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	findFilesAttr.cpp
* Brief: 获取所有文件和其属性
* Source:
* Status: 没有调通
* Date:	[1/30/2015 jmy]
************************************************************************/
#include <io.h>  //_finddata_的声明文件
#include <iostream>  
#include <string>  

using namespace std;  
  
void findFileAttr(string path)  
{  
    _finddata_t file;  
    long longf;  
  
    //_findfirst返回的是long型; long __cdecl _findfirst(const char *, struct _finddata_t *)  
    if((longf = _findfirst(path.c_str(), &file))==-1l) {  
        cout<<"文件没有找到!/n";  
    }  
    else  
    {  
        cout<<"/n文件列表:/n";  
        //int __cdecl _findnext(long, struct _finddata_t *);如果找到下个文件的名字成功的话就返回0,否则返回-1  
        string tempName;  
        while( _findnext( longf, &file ) == 0 )  
        {  
            tempName = "";  
            tempName = file.name;  
            if (tempName == "..") {  
                continue;  
            }  
            cout<<file.name;  
			//文件属性判断
            if(file.attrib == _A_NORMAL) {  
                cout<<" 普通文件 ";  
            }  
            else if(file.attrib == _A_RDONLY) {  
                cout<<"  只读文件  ";  
            }  
            else if(file.attrib == _A_HIDDEN ){  
                cout<<"  隐藏文件  ";  
            }  
            else if(file.attrib == _A_SYSTEM ){  
                cout<<"  系统文件  ";  
            }  
            else if(file.attrib == _A_SUBDIR) {  
                cout<<"  子目录  ";  
            }  
            else {  
                cout<<"  存档文件  ";  
            }  

            cout<<endl;  
        }  
    }  
  
    _findclose(longf);  
  
}  

//功能测试区
//int main()
//{
//	//Mat src = imread("");
//
//	findFileAttr("E:\\360YPan\\Git\\C++_Github\\C++Study\\Source\\fileOpera");
//    cin.get();
//	return 0;
//}