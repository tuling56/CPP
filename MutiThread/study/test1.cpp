/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	test1.cpp
* Brief: CreateThread()��ʼ���߳�ѧϰ
* Reference:http://blog.chinaunix.net/uid-25799257-id-3889830.html
* Status: 
* Date:	[6/2/2015 jmy]
************************************************************************/
#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParamenters);


int winthread_test1(int argc, char* argv[])
{
	int i = 0;
	DWORD test = 0;    ///< 0��ʾ��һ�����߳�
	HANDLE handle;
	DWORD numThreadId = 0;

	for (i = 0; i < 6; ++i)
	{
		///< �̴߳�����Ϻ�����ִ�С��ɵ�5������������
		handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)&test, 0, &numThreadId);
		if (handle)
		{
			Sleep(1000);        ///< Ϊ����testÿ���ǲ�ͬ��ֵ
			test = numThreadId;    ///< ��ʾ"��һ��"���߳��߳�ID
			printf("thread %lld success start...\n", numThreadId);
			CloseHandle(handle);
		}
	}
	Sleep(1000);

	getchar();
	return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	if (0 == *((DWORD *)lpParameter))
	{
		printf("currunt thread is run\n");
	}
	else
	{
		printf("forward threadID is %lld\n", *((DWORD *)lpParameter));
	}

	return 0;
}

