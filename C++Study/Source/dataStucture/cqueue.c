#include <stdio.h>

const int MAXN=50;
//用数组实现队列
int queue[MAXN];

int cqueue()
{
	//初始化
	int n,front,rear;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)
	{
		queue[i]=i+1;
	}

	//数组的长度大于2则重复进行操作
         //数组的取数组的前两个，第一个拿出，第二个放回到数组尾部
    front=0;
    rear=n;
    while(front<rear)
    {
    	printf("%d\n",queue[front++]); //输出并抛弃队首元素
    	queue[rear++]=queue[front++]; //队首元素转移至队尾
    }

    printf("Data Processed:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\n",queue[i]);
    }

    getchar();
    getchar();


	return 0;
}