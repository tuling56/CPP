//

using namespace System;
using namespace Systme::Threading;


void cputime()
{

	int busyTime=10;
	int idleTime=busyTime;  //CPU50%的占用率

	long int startTime=0;
	while (true)
	{
		startTime=GetTickCount();
		//busy loop
		while ((GetTickCount()-startTime)<=busyTime)
		{
			;
		}

		//idle loop
		Sleep(idleTime);

	}

}