/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	MutiThread.cpp
* Brief: 这是2个线程模拟卖火车票的小程序
* Source:http://bbs.csdn.net/topics/250047065
* Status: 利用的是Windows平台自带的API，多线程的API与系统和平台有关
* Date:	[1/23/2015 jmy]
************************************************************************/
#include <windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI Fun1Proc(LPVOID lpParameter);//thread data
DWORD WINAPI Fun2Proc(LPVOID lpParameter);//thread data

int index = 0;
int tickets = 10;
HANDLE hMutex;

void winthread_test3()
{
	HANDLE hThread1;
	HANDLE hThread2;
	
	//创建线程
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	//创建互斥对象，不允许两个实例同时运行
	hMutex = CreateMutex(NULL, TRUE, "tickets");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			cout << "only one instance can run!" << endl;
			return;
		}
	}
	WaitForSingleObject(hMutex, INFINITE);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);

	Sleep(4000);

	getchar();
}

//线程1的入口函数
DWORD WINAPI Fun1Proc(LPVOID lpParameter)//thread data
{
	while (true)
	{
		ReleaseMutex(hMutex);
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "thread 1 sell ticket :" << tickets-- << endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}

	return 0;
}

//线程2的入口函数
DWORD WINAPI Fun2Proc(LPVOID lpParameter)//thread data
{
	while (true)
	{
		ReleaseMutex(hMutex);
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "thread 2 sell ticket :" << tickets-- << endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}

	return 0;
}


//功能测试区
//int main()
//{
//	MutiThread();
//	return 0;
//}