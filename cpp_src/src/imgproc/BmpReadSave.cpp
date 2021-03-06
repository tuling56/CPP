#include <math.h>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;


/*以下该模块是完成BMP图像(彩色图像是24bit,RGB各8bit)的像素获取，并存在文件名为像素.txt中*/
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
int biBitCount;//图像类型，每像素位数
RGBQUAD *pColorTable;//颜色表指针

//读图像的位图数据、宽、高、颜色表及每像素位数等数据进内存，存放在相应的全局变量中
bool readBmp(char *bmpName) 
{
	FILE *fp=fopen(bmpName,"rb");//二进制读方式打开指定的图像文件
	if(fp==0) return 0;
	
	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER),0);
	
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;  
	fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	
	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	
	//如果读取的图像是灰度图，灰度图像有颜色表，且颜色表表项为256
	if(biBitCount==8)
	{
		//申请颜色表所需要的空间，
		pColorTable=new RGBQUAD[256];
		//读颜色表进内存
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}

	//申请位图数据所需要的空间，
	pBmpBuf=new unsigned char[lineByte * bmpHeight];
	//读位图数据进内存
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
	fclose(fp);
	return 1;
}


//保存图像，给定一个图像位图数据、宽、高、每像素所占的位数、颜色表指针及等信息,将其写到指定文件中
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,int biBitCount, RGBQUAD *pColorTable)
{

	//如果位图数据指针为0，则没有数据传入，函数返回
	if(!imgBuf)	return 0;

	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节（256x4），彩色图像颜色表大小为0（因为彩色图像没有颜色表）
	int colorTablesize=0;
	if(biBitCount==8)	colorTablesize=1024;

	//待存储图像数据每行字节数为4的倍数
	int lineByte=(width * biBitCount/8+3)/4*4;

	//以二进制写的方式打开文件
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;

	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型的编码
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ colorTablesize + lineByte*height;//bfSize是图像文件4个组成部分之和
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits=54+colorTablesize;//bfOffBits是图像文件前3个部分所需空间之和，“54=14（文件头）+40（信息头）”

	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

	//申请位图信息头结构变量，填写信息头信息
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

	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

	//如果灰度图像，有颜色表，写入文件 
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);

	//关闭文件
	fclose(fp);

	return 1;

}

int main()
{

    char readPath[]="12.bmp";    //读入指定BMP文件进内存
    readBmp(readPath);
    //输出图像的信息
    cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" biBitCount="<<biBitCount<<endl;
       
    int lineByte=(bmpWidth*biBitCount/8+3)/4*4;//每行字节数

    //循环变量，针对彩色图像，遍历每像素的三个分量
    int m=0,n=0,count_xiang_su=0;

    //将图像左下角1/4部分置成黑色
    ofstream outfile("图像像素.txt",ios::in|ios::trunc);
    if(!outfile) 
	{
		cout<<"open error!"<<endl;
		exit(1);
    }

    if(biBitCount==8) //对于灰度图像
	{              
		//以下完成图像的分割成8*8小单元，并把像素值存储到指定文本中。由于BMP图像的像素数据是从左下角：由左往右，由上往下逐行扫描的
		int L1=0,hang=63,lie=0;
		//int L2=0;
			  //int fen_ge=8;
		for(int fen_ge_hang=0;fen_ge_hang<8;fen_ge_hang++)//64*64矩阵行循环
		{ 
		 for(int fen_ge_lie=0;fen_ge_lie<8;fen_ge_lie++)//64*64列矩阵循环
		 { 
		  for(L1=hang;L1>hang-8;L1--)//8*8矩阵行
		  {
			for(int L2=lie;L2<lie+8;L2++)//8*8矩阵列
			{
				 m=*(pBmpBuf+L1*lineByte+L2);
				 outfile<<m<<" ";
				 count_xiang_su++;
					if(count_xiang_su%8==0)//每8*8矩阵读入文本文件
					{
						outfile<<endl;
					}
			}
		  }
		 hang=63-fen_ge_hang*8;//64*64矩阵行变换
		 lie+=8;//64*64矩阵列变换
		 //该一行（64）由8个8*8矩阵的行组成
		 }
		 hang-=8;//64*64矩阵的列变换
		 lie=0;//64*64juzhen
		}
	}
  else if(biBitCount==24) //彩色图像
  {
     for(int i=0;i<bmpHeight;i++)
	{
       for(int j=0;j<bmpWidth;j++)
	   { 
     	   for(int k=0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
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
	 cout<<"总的像素个素为:"<<n<<endl;
	 cout<<"----------------------------------------------------"<<endl;
   }
    
    
    char photoname[]="nvcpy.BMP";
    saveBmp(photoname, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);//将图像数据存盘
    
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
    delete []pBmpBuf;
    if(biBitCount==8)   delete []pColorTable;

	return 0;

}
