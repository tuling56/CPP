// tabtenn1.h -- a table-tennis base class
//在该头文件中定义了基类和派生类的数据成员和函数成员

#ifndef TABTENN1_H_
#define TABTENN1_H_
#include <string>
using std::string;
// simple base class
class TableTennisPlayer
{
private:
    string firstname;
    string lastname;
    bool hasTable;
public:
    TableTennisPlayer (const string & fn = "none",
                       const string & ln = "none", 
					   bool ht = false);
    void Name() const;
    bool HasTable() const { return hasTable; };
    void ResetTable(bool v) { hasTable = v; };
};

// simple derived class
//基类的私有部分也成为派生类的一部分，但只能通过基类的公有和保护方法访问

class RatedPlayer : public TableTennisPlayer
{
	//派生类新添加的数据成员
private:
    unsigned int rating;
public:
	//派生类自己的构造函数，调用默认的基类构造函数
    RatedPlayer (unsigned int r = 0, const string & fn = "none",
                 const string & ln = "none", bool ht = false);
	//用基类的对象初始化派生类的成员
    RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
	//派生类新添加的成员函数
    unsigned int Rating() const { return rating; }
    void ResetRating (unsigned int r) {rating = r;}
};

#endif
