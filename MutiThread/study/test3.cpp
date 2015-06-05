/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	MutiThread.cpp
* Brief: ����2���߳�ģ������Ʊ��С����
* Source:http://bbs.csdn.net/topics/250047065
* Status: ���õ���Windowsƽ̨�Դ���API�����̵߳�API��ϵͳ��ƽ̨�й�
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
	
	//�����߳�
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	//����������󣬲���������ʵ��ͬʱ����
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

//�߳�1����ں���
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

//�߳�2����ں���
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


//���ܲ�����
//int main()
//{
//	MutiThread();
//	return 0;
//}