#include <iostream>  
#include <string>  
#include <io.h>  

using namespace std;  
  
void findfile(int argc, char **argv)  
{  
    _finddata_t file;  
    long longf;  
  
    //_findfirst返回的是long型; long __cdecl _findfirst(const char *, struct _finddata_t *)  
    if((longf = _findfirst(argv[1], &file))==-1l)  
    {  
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
            if (tempName == "..")  
            {  
                continue;  
            }  
  
            cout<<file.name;  
           
			//文件属性判断
            if(file.attrib == _A_NORMAL)  
            {  
                cout<<" 普通文件 ";  
            }  
            else if(file.attrib == _A_RDONLY)  
            {  
                cout<<"  只读文件  ";  
            }  
            else if(file.attrib == _A_HIDDEN )  
            {  
                cout<<"  隐藏文件  ";  
            }  
            else if(file.attrib == _A_SYSTEM )  
            {  
                cout<<"  系统文件  ";  
            }  
            else if(file.attrib == _A_SUBDIR)  
            {  
                cout<<"  子目录  ";  
            }  
            else   
            {  
                cout<<"  存档文件  ";  
            }  

            cout<<endl;  
        }  
    }  
  
    _findclose(longf);  
  
}  