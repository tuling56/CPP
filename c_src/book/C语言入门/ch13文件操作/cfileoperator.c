/* operator.c
 
 //读写函数
 字符读写函数 ：fgetc和fputc
字符串读写函数：fgets和fputs
数据块读写函数：freed和fwrite
格式化读写函数：fscanf和fprintf
 
 //定位函数




*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 40

int cfileoperator(void)
{
    FILE *fp;
    char words[MAX];
	char chara;

    if ((fp = fopen("word.txt", "w+")) == NULL)
    {
        fprintf(stdout,"Can't open \"words\" file.\n");
        exit(1);
    }
     
    //演示fgetc()和fputc()的用法
	//发现了的问题，第一个字符不行
	/*
     printf("请输入字符\n");
	 scanf("%c",&chara);
	 fputc(chara,fp);
	 rewind(fp);
	 printf("从文件中取出你刚才输入的字符是%c",fgetc(fp));
	 */
	 
	
	 //演示fgets()和fputs()的用法
	 //gets()不读取换行符？
	 /*
	 while (gets(words) != NULL  && words[0] != '\0') //从命令行读入
	 fputs(words,fp);
	 rewind(fp);
	 fgets(words,12,fp);
	 puts("你刚才输入的单词是：");
	 puts(words);
	 */


	 //演示fread()和fwrite()的用法
	 //fwrite()的第三个参数的作用
	 /*
	 while (gets(words) != NULL  && words[0] != '\0') //从命令行读入
	 fwrite(words,sizeof(char),2,fp);
	 rewind(fp);
	 fread(words,12,1,fp);
	 puts("你刚才输入的内容是：");
	 puts(words);
	 */

	//演示fscanf()和fprinf()的用法
	puts("Enter words to add to the file; press the Enter\n");
	puts("key at the beginning of a line to terminate.");
	while (gets(words) != NULL  && words[0] != '\0')
		fprintf(fp, "%s ", words);   
	puts("你刚才输入的内容是:");
	rewind(fp);           // go back to beginning of file 
	while (fscanf(fp,"%s",words) == 1)
		puts(words);
     

   
   //关闭文件
    if (fclose(fp) != 0)
        fprintf(stderr,"Error closing file\n");

    
    return 0;
}
