/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	queue.cpp
* Brief: 队列学习
* Source:http://blog.csdn.net/xizero00/article/details/6670482
* Status: 
* Date:	[1/8/2015 jmy]
************************************************************************/
#include "queue.h"  

int main( int argc , char **argv )  
{  
	Queue<int> q;  
	int data[] = { 1, 2, 4 ,5 };  

	//入队列  
	for( int i = 0 ; i < 4 ; i++ )  
	{  
		q.push( data[i] );  
	}  
	cout << "q队列元素如下：" << endl;  
	q.ShowElements();  

	Queue<int> p;  

	//复制队列元素  
	p = q;  

	cout << "p队列元素如下(它是复制的q队列的元素):" << endl;  
	p.ShowElements();  

	cout << "对p队列进行出队列操作" << endl;  
	p.pop();  
	p.ShowElements();  

	cout << "出队列操作进行3次" << endl;  
	p.pop();  
	p.pop();  
	p.pop();  
	p.ShowElements();  


	return 0;  
}