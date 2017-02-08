/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	pthread_test.cpp
* Brief: Windows 7 64bit��Visual Studio 2010�°�װ��ʹ��Pthread-w32 2.8
* Reference:http://blog.sina.com.cn/s/blog_6e0693f70100txlc.html
*           http://www.cppblog.com/saha/articles/189802.html Pthreadѧϰ
* Status: 
* Date:	[6/2/2015 jmy]
************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <iostream>
#include <windows.h>

using namespace std;

#define  NUM_THREADS 5   //�����߳���

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
	pthread_attr_init(&attr); //�߳����Գ�ʼ��
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	pthread_create(&pid, &attr, Function_t, NULL);
	printf("====\n");
	getchar();
	pthread_attr_destroy(&attr);
	*/
	
	pthread_t tids[NUM_THREADS]; //�������߳���
	for (int i = 0; i < NUM_THREADS;i++)
	{
		int ret = pthread_create(&tids[i], NULL, say_hello, NULL); //�������������߳�id���̲߳������߳����к�������ʼ��ַ�����к����Ĳ���
		if (ret!=0) //�����̳߳ɹ�����0
		{
			cout << "pthread creat error:error_code=" << ret << endl;
		}
	}
	pthread_exit(NULL); //�ȴ������߳̽����󣬽��̲Ž������������ǿ�ƽ������̴߳���δ��ֹ״̬


	getchar();
	return 0;
}
