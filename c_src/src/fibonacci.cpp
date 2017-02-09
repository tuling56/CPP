#include <iostream>
#include <stdio.h>

using namespace std;

//非递归实现
int Fibonacci2(int n)
{
	int *num=new int[n]; //堆内存分配的方式

	num[0]=num[1]=num[2]=1;

	for (int i=3;i<n;i++)
	{
		num[i]=num[i-1]+num[i-3];
	}

	int ret=num[n-1];
	delete [] num;
	return ret;
}



