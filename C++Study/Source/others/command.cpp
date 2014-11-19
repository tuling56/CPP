#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
	IplImage* pImg=NULL; //声明IplImage指针
	//载入图像
	if( argc == 2 && (pImg = cvLoadImage( argv[1], 1)) != 0 )
		//[[此处的argc==2是否需要改成argc==1？我改了之后才能运行成功。求大牛解惑]] 
		// 在"属性"|"debug"|里的command arguments 里加入参数(一个路径:要打开的文件路径) 
		//这时 argc==2 就合理了
		//注意是相对路径1.png
	{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", pImg );//显示图像

		cvWaitKey(0); //等待按键

		cvDestroyWindow( "Image" );//销毁窗口
		cvReleaseImage( &pImg ); //释放图像

		cvWaitKey(0); //等待按键

	}

	else{
		cout<<"加载失败"<<endl;
		cvWaitKey(0); //等待按键

	}
	

	return -1;
}