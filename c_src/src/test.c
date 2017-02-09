#include <stdio.h>
#include <stdlib.h>

void test(void)
{
	/*int a=5;
	printf("%d %p",a,&a);*/
	/*char name[20];
	fputs("ÇëÊäÈë×Ö·û£º\n",stdout);
	gets(name);
	puts(name);
	fputs(name,stdout);
	printf("intÐÍÕ¼µÄ×Ö½ÚÊý£º\n%d",sizeof(int));*/

	char *str="haeede";
	puts(str);
		getchar();
}

int test1()
{
	int i;
	for (i=0;i<5;i++)
	{
		printf("%d",i);
	}
	printf("%d",i);
	return 0;
}


//字符串转整型
int m_strtol()
{
	char *string, *stopstring;
	double x;
	int base;
	long l;
	unsigned long ul;
	string = "3.1415926This stopped it";
	x = strtod( string, &stopstring );
	printf( "string = %s\n", string );
	printf(" strtod = %f\n", x );
	printf(" Stopped scan at: %s\n\n", stopstring );
	string = "-10110134932This stopped it";
	l = strtol( string, &stopstring, 10 );
	printf( "string = %s", string );
	printf(" strtol = %ld", l );
	printf(" Stopped scan at: %s", stopstring );
	string = "10110134932";
	printf( "string = %s\n", string );
	/* Convert string using base 2, 4, and 8: */
	for( base = 2; base <= 8; base *= 2 )
	{
		/* Convert the string: */
		ul = strtoul( string, &stopstring, base );
		printf( " strtol = %ld (base %d)\n", ul, base );
		printf( " Stopped scan at: %s\n", stopstring );
	}
	return 0;
}

int test2()
{
    const char*strnum="1234567";
    printf("转换成的数字是:%d\n",atol(strnum));
    return 0;
}


//程序入口
int main()
{
    test2();
    return 0;

}

