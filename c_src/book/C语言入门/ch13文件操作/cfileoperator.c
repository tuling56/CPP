/* operator.c
 
 //��д����
 �ַ���д���� ��fgetc��fputc
�ַ�����д������fgets��fputs
���ݿ��д������freed��fwrite
��ʽ����д������fscanf��fprintf
 
 //��λ����




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
     
    //��ʾfgetc()��fputc()���÷�
	//�����˵����⣬��һ���ַ�����
	/*
     printf("�������ַ�\n");
	 scanf("%c",&chara);
	 fputc(chara,fp);
	 rewind(fp);
	 printf("���ļ���ȡ����ղ�������ַ���%c",fgetc(fp));
	 */
	 
	
	 //��ʾfgets()��fputs()���÷�
	 //gets()����ȡ���з���
	 /*
	 while (gets(words) != NULL  && words[0] != '\0') //�������ж���
	 fputs(words,fp);
	 rewind(fp);
	 fgets(words,12,fp);
	 puts("��ղ�����ĵ����ǣ�");
	 puts(words);
	 */


	 //��ʾfread()��fwrite()���÷�
	 //fwrite()�ĵ���������������
	 /*
	 while (gets(words) != NULL  && words[0] != '\0') //�������ж���
	 fwrite(words,sizeof(char),2,fp);
	 rewind(fp);
	 fread(words,12,1,fp);
	 puts("��ղ�����������ǣ�");
	 puts(words);
	 */

	//��ʾfscanf()��fprinf()���÷�
	puts("Enter words to add to the file; press the Enter\n");
	puts("key at the beginning of a line to terminate.");
	while (gets(words) != NULL  && words[0] != '\0')
		fprintf(fp, "%s ", words);   
	puts("��ղ������������:");
	rewind(fp);           // go back to beginning of file 
	while (fscanf(fp,"%s",words) == 1)
		puts(words);
     

   
   //�ر��ļ�
    if (fclose(fp) != 0)
        fprintf(stderr,"Error closing file\n");

    
    return 0;
}
