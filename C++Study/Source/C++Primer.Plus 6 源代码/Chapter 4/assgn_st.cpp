/* assgn_st.cpp -- assigning structures
 *使用“=”将一个结构赋给另一个同类型的结构，这样结构中的每个成员都将被设置为
 *另一个结构中相应成员的值，即使成员是数组
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

	//C++11中结构体的列表初始化，并且“=”是可选的，但在C99中目前“=”不能去掉，其它都一样
    inflatable bouquet =
    {
        "sunflowers",
		{1,23,4,5},
        0.20,
        12.49
    };
	//如果初始化括号里没有包含任何东西，则各个成员都将被初始化为0
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
