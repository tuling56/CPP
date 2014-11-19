#include <iostream>
#include <vector>
#include <valarray>
#include <algorithm>

int main()
{
	using namespace std;
    vector<double> data;//创建存储容器
    double temp;

    while(cin>>temp&&temp>0)
    	data.push_back(temp);//数据存储到容器中
    sort(data.begin(),data.end());

    int size=data.size();
    valarray<double> val_numbers(size);//创建可变数组

    for (int i = 0; i < size; ++i)  //复制数据
    {
    	val_numbers[i]=data[i];
    }

    valarray<double> val_sqrts(size);
    val_sqrts=sqrt(val_numbers); //对valarray进行整体运算

    valarray<double> val_results(size);
    val_results=val_numbers+2.0*val_sqrts; //更复杂的运算

    //显示部分
    cout.setf(ios_base::fixed);
    cout.precision(4);
    for (int i = 0; i < size; ++i)
    {
    	cout.width(8);
    	cout<<val_numbers[i]<<":"<<val_sqrts[i]<<":"<<val_results[i]<<endl;
    }

	cin.get();
	return 0;
}