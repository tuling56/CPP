//tabtenn1.cpp -- simple base-class methods
#include "tabtenn1.h"
#include <iostream>

//���๹�캯��
TableTennisPlayer::TableTennisPlayer (const string & fn, 
    const string & ln, bool ht) : firstname(fn),
	    lastname(ln), hasTable(ht) {}

//�����Ա����
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}

// ������RatedPlayer��һ�ֹ��캯��
RatedPlayer::RatedPlayer(unsigned int r, const string & fn,
     const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{
    rating = r;
}

//������ĵڶ��ֹ��캯��
RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp)
    : TableTennisPlayer(tp), rating(r)
{
}
