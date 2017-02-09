//tabtenn0.cpp -- simple base-class methods
#include "tabtenn0.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer (const string & fn, 
									  const string & ln, 
									  bool ht) 
									  : firstname(fn),lastname(ln), hasTable(ht) 
{
	//�չ��캯���壬����ʹ���˱�׼��ʼ���б�����Ҳ��������������
	//firstname=fn;
	//lastname=ln;
	//hasTable=ht;
}

//��ʾ���ֵĳ�Ա����
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}
