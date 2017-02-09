#include <stdio.h>

#define SIZE 3

//原型
void arr_sum1(int arr[]);
/*	
 声明的时候下面的几种的形式等价
 void arr_sum1(int arr[]);
 void arr_sum1(int []);
 void arr_sum1(int *arr);
 void arr_sum1(int *)

*/

void arr_sum2(int arr[]);

int arr_sum(void)
{
	int arr[SIZE]={1,2,4};
	
	arr_sum2(arr);
	arr_sum1(arr);
	
	getchar();
	return 0;
}


void arr_sum1(int *arr)  //地址传递
{
	int index;
	int total=0;
	for (index=0;index<SIZE;index++)
	{
		arr[index]+=1;
		total+=arr[index];
	}
	printf("arr1数组元素和为：%d\n",total);
}

//定义
/*	定义的时候不可以省略名称
 *  下面的几种形式等价
 *  void arr_sum2(int arr[])
    {//代码段}
	void arr_sum2(int *arr)
	{//代码段}

*/
void arr_sum2(int *arr)
{
	int index;
	int total=0;
	for (index=0;index<SIZE;index++)
	{
		total+=arr[index];
	}
	printf("arr2数组元素和为：%d\n",total);
}