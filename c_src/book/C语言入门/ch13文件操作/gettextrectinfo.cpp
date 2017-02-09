#include <stdio.h>
#include <stdlib.h>

struct textrect{
	int lu_x;
	int lu_y;
	int rd_x;
	int rd_y;
};

int gettextrectinfo(void)
{ 
	char buf[100];
	char col[100][30];
	int n=0;
	FILE *fp = fopen("test.txt", "r");   
	while (fgets(buf, 100, fp) != NULL) 
	{
		puts(buf);
		if ( sscanf(buf,"%s",col[n]) == 1)
		{printf("%s\n", col[n]);  n++; };
	} 
	fclose(fp);
	return 0;
}
