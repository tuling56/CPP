// tabtenn1.h -- a table-tennis base class
//�ڸ�ͷ�ļ��ж����˻��������������ݳ�Ա�ͺ�����Ա

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
//�����˽�в���Ҳ��Ϊ�������һ���֣���ֻ��ͨ������Ĺ��кͱ�����������

class RatedPlayer : public TableTennisPlayer
{
	//����������ӵ����ݳ�Ա
private:
    unsigned int rating;
public:
	//�������Լ��Ĺ��캯��������Ĭ�ϵĻ��๹�캯��
    RatedPlayer (unsigned int r = 0, const string & fn = "none",
                 const string & ln = "none", bool ht = false);
	//�û���Ķ����ʼ��������ĳ�Ա
    RatedPlayer(unsigned int r, const TableTennisPlayer & tp);
	//����������ӵĳ�Ա����
    unsigned int Rating() const { return rating; }
    void ResetRating (unsigned int r) {rating = r;}
};

#endif
