#include <iostream>  
#include <string>  
#include <io.h>  

using namespace std;  
  
void findfile(int argc, char **argv)  
{  
    _finddata_t file;  
    long longf;  
  
    //_findfirst���ص���long��; long __cdecl _findfirst(const char *, struct _finddata_t *)  
    if((longf = _findfirst(argv[1], &file))==-1l)  
    {  
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
            if (tempName == "..")  
            {  
                continue;  
            }  
  
            cout<<file.name;  
           
			//�ļ������ж�
            if(file.attrib == _A_NORMAL)  
            {  
                cout<<" ��ͨ�ļ� ";  
            }  
            else if(file.attrib == _A_RDONLY)  
            {  
                cout<<"  ֻ���ļ�  ";  
            }  
            else if(file.attrib == _A_HIDDEN )  
            {  
                cout<<"  �����ļ�  ";  
            }  
            else if(file.attrib == _A_SYSTEM )  
            {  
                cout<<"  ϵͳ�ļ�  ";  
            }  
            else if(file.attrib == _A_SUBDIR)  
            {  
                cout<<"  ��Ŀ¼  ";  
            }  
            else   
            {  
                cout<<"  �浵�ļ�  ";  
            }  

            cout<<endl;  
        }  
    }  
  
    _findclose(longf);  
  
}  