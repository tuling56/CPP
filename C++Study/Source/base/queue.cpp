/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	queue.cpp
* Brief: ����ѧϰ
* Source:http://blog.csdn.net/xizero00/article/details/6670482
* Status: 
* Date:	[1/8/2015 jmy]
************************************************************************/
#include "queue.h"  

int main( int argc , char **argv )  
{  
	Queue<int> q;  
	int data[] = { 1, 2, 4 ,5 };  

	//�����  
	for( int i = 0 ; i < 4 ; i++ )  
	{  
		q.push( data[i] );  
	}  
	cout << "q����Ԫ�����£�" << endl;  
	q.ShowElements();  

	Queue<int> p;  

	//���ƶ���Ԫ��  
	p = q;  

	cout << "p����Ԫ������(���Ǹ��Ƶ�q���е�Ԫ��):" << endl;  
	p.ShowElements();  

	cout << "��p���н��г����в���" << endl;  
	p.pop();  
	p.ShowElements();  

	cout << "�����в�������3��" << endl;  
	p.pop();  
	p.pop();  
	p.pop();  
	p.ShowElements();  


	return 0;  
}