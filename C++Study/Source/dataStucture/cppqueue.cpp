//用C++的标准模板库实现队列
#include <cstdio>
#include <queue>

using namespace std;

queue<int> q;

int cppqueue()
{
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)
	{
		q.push(i+1); //队列初始化
	}

	while(!q.empty())
	{
		printf("%d\n",q.front());//打印队列首元素
		q.pop();//抛弃队列首元素
		q.push(q.front());//取队头加入队尾
		q.pop();//抛弃队列首元素

	}
	
	getchar();
	getchar();
	return 0;
}