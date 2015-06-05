/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	pthread_test.cpp
* Brief: Windows 7 64bit和Visual Studio 2010下安装及使用Pthread-w32 2.8
* Reference:http://blog.sina.com.cn/s/blog_6e0693f70100txlc.html
*           http://www.cppblog.com/saha/articles/189802.html Pthread学习
* Status: 
* Date:	[6/2/2015 jmy]
************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <iostream>
#include <windows.h>

using namespace std;

#define  NUM_THREADS 5   //定义线程数

void* Function_t(void* Param)
{
	printf("Thread Starts.\n");
	pthread_t myid = pthread_self();
	printf("Thread ID=%d ", myid);

	return NULL;
}

void *say_hello(void*args)
{
	cout << "hello..." << endl;
	Sleep(1000);
	return NULL;
}


int pthread_test()
{
	/*
	pthread_t pid;
	pthread_attr_t attr;
	pthread_attr_init(&attr); //线程属性初始化
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	pthread_create(&pid, &attr, Function_t, NULL);
	printf("====\n");
	getchar();
	pthread_attr_destroy(&attr);
	*/
	
	pthread_t tids[NUM_THREADS]; //创建的线程数
	for (int i = 0; i < NUM_THREADS;i++)
	{
		int ret = pthread_create(&tids[i], NULL, say_hello, NULL); //参数：创建的线程id，线程参数，线程运行函数的起始地址，运行函数的参数
		if (ret!=0) //创建线程成功返回0
		{
			cout << "pthread creat error:error_code=" << ret << endl;
		}
	}
	pthread_exit(NULL); //等待各个线程结束后，进程才结束，否则进程强制结束，线程处于未终止状态


	getchar();
	return 0;
}
