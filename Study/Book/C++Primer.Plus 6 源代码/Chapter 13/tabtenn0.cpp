//tabtenn0.cpp -- simple base-class methods
#include "tabtenn0.h"
#include <iostream>

TableTennisPlayer::TableTennisPlayer (const string & fn, 
									  const string & ln, 
									  bool ht) 
									  : firstname(fn),lastname(ln), hasTable(ht) 
{
	//空构造函数体，这里使用了标准初始化列表方法，也可以像下面这样
	//firstname=fn;
	//lastname=ln;
	//hasTable=ht;
}

//显示名字的成员函数
void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}
