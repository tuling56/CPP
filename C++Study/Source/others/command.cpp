#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
	IplImage* pImg=NULL; //����IplImageָ��
	//����ͼ��
	if( argc == 2 && (pImg = cvLoadImage( argv[1], 1)) != 0 )
		//[[�˴���argc==2�Ƿ���Ҫ�ĳ�argc==1���Ҹ���֮��������гɹ������ţ���]] 
		// ��"����"|"debug"|���command arguments ��������(һ��·��:Ҫ�򿪵��ļ�·��) 
		//��ʱ argc==2 �ͺ�����
		//ע�������·��1.png
	{
		cvNamedWindow( "Image", 1 );//��������
		cvShowImage( "Image", pImg );//��ʾͼ��

		cvWaitKey(0); //�ȴ�����

		cvDestroyWindow( "Image" );//���ٴ���
		cvReleaseImage( &pImg ); //�ͷ�ͼ��

		cvWaitKey(0); //�ȴ�����

	}

	else{
		cout<<"����ʧ��"<<endl;
		cvWaitKey(0); //�ȴ�����

	}
	

	return -1;
}