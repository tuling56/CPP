//tabtenn1.cpp -- simple base-class methods
#include "tabtenn1.h"
#include <iostream>

//基类构造函数
TableTennisPlayer::TableTennisPlayer (const string & fn, 
    const string & ln, bool ht) : firstname(fn),
	    lastname(ln), hasTable(ht) {}

//基类成员函数
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}

// 派生类RatedPlayer的一种构造函数
RatedPlayer::RatedPlayer(unsigned int r, const string & fn,
     const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{
    rating = r;
}

//派生类的第二种构造函数
RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp)
    : TableTennisPlayer(tp), rating(r)
{
}
