/* assgn_st.cpp -- assigning structures
 *ʹ�á�=����һ���ṹ������һ��ͬ���͵Ľṹ�������ṹ�е�ÿ����Ա����������Ϊ
 *��һ���ṹ����Ӧ��Ա��ֵ����ʹ��Ա������
 */
#include <iostream>

struct inflatable
{
    char name[20];
	int num[5];
    float volume;
    double price;
};
int assgn_st()
{
    using namespace std;

	//C++11�нṹ����б��ʼ�������ҡ�=���ǿ�ѡ�ģ�����C99��Ŀǰ��=������ȥ����������һ��
    inflatable bouquet =
    {
        "sunflowers",
		{1,23,4,5},
        0.20,
        12.49
    };
	//�����ʼ��������û�а����κζ������������Ա��������ʼ��Ϊ0
	inflatable choice={};

    
	cout << "bouquet: " 
		 << bouquet.name << " for $"
		 << bouquet.price << endl;
	cout << "num:"<<bouquet.num[1]<<endl;

    choice = bouquet;  // assign one structure to another
    cout << "choice: " 
		 << choice.name << " for $"
		 << choice.price << endl;
    cout << "num:"<<choice.num[1]<<endl;
	
    
	
	// cin.get();
    return 0; 
}
