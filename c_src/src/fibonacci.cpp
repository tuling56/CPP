#include <iostream>
#include <stdio.h>

using namespace std;

//�ǵݹ�ʵ��
int Fibonacci2(int n)
{
	int *num=new int[n]; //���ڴ����ķ�ʽ

	num[0]=num[1]=num[2]=1;

	for (int i=3;i<n;i++)
	{
		num[i]=num[i-1]+num[i-3];
	}

	int ret=num[n-1];
	delete [] num;
	return ret;
}



