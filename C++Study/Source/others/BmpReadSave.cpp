#include <math.h>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;


/*���¸�ģ�������BMPͼ��(��ɫͼ����24bit,RGB��8bit)�����ػ�ȡ���������ļ���Ϊ����.txt��*/
unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
int biBitCount;//ͼ�����ͣ�ÿ����λ��
RGBQUAD *pColorTable;//��ɫ��ָ��

//��ͼ���λͼ���ݡ����ߡ���ɫ��ÿ����λ�������ݽ��ڴ棬�������Ӧ��ȫ�ֱ�����
bool readBmp(char *bmpName) 
{
	FILE *fp=fopen(bmpName,"rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
	if(fp==0) return 0;
	
	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER),0);
	
	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;  
	fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	
	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	
	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	
	//�����ȡ��ͼ���ǻҶ�ͼ���Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if(biBitCount==8)
	{
		//������ɫ������Ҫ�Ŀռ䣬
		pColorTable=new RGBQUAD[256];
		//����ɫ����ڴ�
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}

	//����λͼ��������Ҫ�Ŀռ䣬
	pBmpBuf=new unsigned char[lineByte * bmpHeight];
	//��λͼ���ݽ��ڴ�
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
	fclose(fp);
	return 1;
}


//����ͼ�񣬸���һ��ͼ��λͼ���ݡ����ߡ�ÿ������ռ��λ������ɫ��ָ�뼰����Ϣ,����д��ָ���ļ���
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,int biBitCount, RGBQUAD *pColorTable)
{

	//���λͼ����ָ��Ϊ0����û�����ݴ��룬��������
	if(!imgBuf)	return 0;

	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ�256x4������ɫͼ����ɫ���СΪ0����Ϊ��ɫͼ��û����ɫ��
	int colorTablesize=0;
	if(biBitCount==8)	colorTablesize=1024;

	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte=(width * biBitCount/8+3)/4*4;

	//�Զ�����д�ķ�ʽ���ļ�
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;

	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp���͵ı���
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ colorTablesize + lineByte*height;//bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits=54+colorTablesize;//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮�ͣ���54=14���ļ�ͷ��+40����Ϣͷ����

	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head; 
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;

	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

	//����Ҷ�ͼ������ɫ��д���ļ� 
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height*lineByte, 1, fp);

	//�ر��ļ�
	fclose(fp);

	return 1;

}

int main()
{

    char readPath[]="12.bmp";    //����ָ��BMP�ļ����ڴ�
    readBmp(readPath);
    //���ͼ�����Ϣ
    cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" biBitCount="<<biBitCount<<endl;
       
    int lineByte=(bmpWidth*biBitCount/8+3)/4*4;//ÿ���ֽ���

    //ѭ����������Բ�ɫͼ�񣬱���ÿ���ص���������
    int m=0,n=0,count_xiang_su=0;

    //��ͼ�����½�1/4�����óɺ�ɫ
    ofstream outfile("ͼ������.txt",ios::in|ios::trunc);
    if(!outfile) 
	{
		cout<<"open error!"<<endl;
		exit(1);
    }

    if(biBitCount==8) //���ڻҶ�ͼ��
	{              
		//�������ͼ��ķָ��8*8С��Ԫ����������ֵ�洢��ָ���ı��С�����BMPͼ������������Ǵ����½ǣ��������ң�������������ɨ���
		int L1=0,hang=63,lie=0;
		//int L2=0;
			  //int fen_ge=8;
		for(int fen_ge_hang=0;fen_ge_hang<8;fen_ge_hang++)//64*64������ѭ��
		{ 
		 for(int fen_ge_lie=0;fen_ge_lie<8;fen_ge_lie++)//64*64�о���ѭ��
		 { 
		  for(L1=hang;L1>hang-8;L1--)//8*8������
		  {
			for(int L2=lie;L2<lie+8;L2++)//8*8������
			{
				 m=*(pBmpBuf+L1*lineByte+L2);
				 outfile<<m<<" ";
				 count_xiang_su++;
					if(count_xiang_su%8==0)//ÿ8*8��������ı��ļ�
					{
						outfile<<endl;
					}
			}
		  }
		 hang=63-fen_ge_hang*8;//64*64�����б任
		 lie+=8;//64*64�����б任
		 //��һ�У�64����8��8*8����������
		 }
		 hang-=8;//64*64������б任
		 lie=0;//64*64juzhen
		}
	}
  else if(biBitCount==24) //��ɫͼ��
  {
     for(int i=0;i<bmpHeight;i++)
	{
       for(int j=0;j<bmpWidth;j++)
	   { 
     	   for(int k=0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				 //*(pBmpBuf+i*lineByte+j*3+k)-=40;
				 m=*(pBmpBuf+i*lineByte+j*3+k);
			     outfile<<m<<" ";
				 count_xiang_su++;
				 if(count_xiang_su%8==0)
				 {
				   outfile<<endl;
				 }
			}
		  n++;
	   }
	}
	 cout<<"�ܵ����ظ���Ϊ:"<<n<<endl;
	 cout<<"----------------------------------------------------"<<endl;
   }
    
    
    char photoname[]="nvcpy.BMP";
    saveBmp(photoname, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);//��ͼ�����ݴ���
    
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
    delete []pBmpBuf;
    if(biBitCount==8)   delete []pColorTable;

	return 0;

}
