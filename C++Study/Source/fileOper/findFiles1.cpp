//Sourece:http://fushengfei.iteye.com/blog/1100241

#include<iostream>     
#include<string>     
#include<io.h>    
using namespace std;


void  visit(string path, int layer)
{
	struct _finddata_t   filefind;
	string  curr = path + "\\*.*";
	int   done = 0, i, handle;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)return;
	while (!(done = _findnext(handle, &filefind)))
	{
		printf("%s\n", filefind.name);
		if (!strcmp(filefind.name, "..")){
			continue;
		}
		for (i = 0; i < layer; i++)cout << "     ";
		if ((_A_SUBDIR == filefind.attrib)) //��Ŀ¼  
		{
			printf("----------%s\n", filefind.name);
			cout << filefind.name << "(dir)" << endl;
			curr = path + "\\" + filefind.name;
		}
		else//����Ŀ¼�����ļ�       
		{
			cout << path + "\\" + filefind.name << endl;
		}
	}
	_findclose(handle);
}


int   main()
{
	string   path="samples";
	//cout << "������Ŀ¼" << endl;
	//cin >> path;
	visit(path, 1);
	system("PAUSE");
	return   0;
}
