#include <stdio.h>

#define SIZE 3

//ԭ��
void arr_sum1(int arr[]);
/*	
 ������ʱ������ļ��ֵ���ʽ�ȼ�
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


void arr_sum1(int *arr)  //��ַ����
{
	int index;
	int total=0;
	for (index=0;index<SIZE;index++)
	{
		arr[index]+=1;
		total+=arr[index];
	}
	printf("arr1����Ԫ�غ�Ϊ��%d\n",total);
}

//����
/*	�����ʱ�򲻿���ʡ������
 *  ����ļ�����ʽ�ȼ�
 *  void arr_sum2(int arr[])
    {//�����}
	void arr_sum2(int *arr)
	{//�����}

*/
void arr_sum2(int *arr)
{
	int index;
	int total=0;
	for (index=0;index<SIZE;index++)
	{
		total+=arr[index];
	}
	printf("arr2����Ԫ�غ�Ϊ��%d\n",total);
}