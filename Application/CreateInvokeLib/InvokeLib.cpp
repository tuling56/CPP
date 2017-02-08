/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	InvokeLib.cpp
* Brief: 生成和调用静态库文件
* Source: http://www.cnblogs.com/krisdy/archive/2009/06/17/1505042.html
* Status: 
* Date:	[1/30/2015 jmy]
************************************************************************/
#include "CreateLib.h"
#include <stdio.h>

#pragma comment(lib,"CreateInvokeLib.lib")//链接库文件

int main()
{
	myclass aa;
	aa.show();
	
	getchar();
	return 0;
}