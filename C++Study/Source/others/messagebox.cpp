#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	printf("Hello, world\n");
    MessageBox(NULL,TEXT("待预测图像不存在！"),TEXT("提示"),MB_ICONWARNING);
	
	return 0;
}
