/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	OpenMP.cpp
* Brief: OpenMP多线程处理
* Source:http://www.cnblogs.com/yangyangcv/archive/2012/03/23/2413335.html
* Status: 
* Date:	[1/12/2015 jmy]
************************************************************************/
#include <iostream>
#include <time.h>

void test()
{
	int a = 0;
	for (int i=0;i<100000000;i++)
		a++;
}


int main()
{
	clock_t t1 = clock();
#pragma omp parallel for
	for (int i=0;i<8;i++)
		test();
	clock_t t2 = clock();
	
	std::cout<<"time: "<<t2-t1<<std::endl;
	std::cin.get();
	return 0;
}