/************************************************************************
* Copyright(c) 2015 tuling56
*
* File:	fileRead.cpp
* Brief: 文件读取,把训练数据文件读取到Mat类型的data和response结构中
* Source:OpenCV的letter_recong.cpp文件
* Status: 
* Date:	[3/6/2015 jmy]
************************************************************************/
/*文件存储格式
T,2,8,3,5,1,8,13,0,6,6,10,8,0,8,0,8
I,5,12,3,7,2,10,5,5,4,13,3,9,2,8,4,10
D,4,11,6,8,6,10,6,2,6,10,3,7,3,7,3,9
......
*/

#include <stdio.h>
#include <opencv2/core/core.hpp>

using namespace cv;

void txtfileRead(const char* _dataFileName)
{
	// 读取数据
	const int MAX_FEATURE = 100;
	const int VAR_COUNT = 16;
	const int NSAMPLES_ALL = 20000;
	
	FILE* f = fopen(_dataFileName, "rt");

	char buf[MAX_FEATURE+2];
	float* el_ptr;

	Mat data(NSAMPLES_ALL, 16, CV_32F);
	Mat responses(NSAMPLES_ALL, 1, CV_32F);

	el_ptr = new float[VAR_COUNT+1];

	for(int i=0; i<NSAMPLES_ALL; i++)
	{
		if (!fgets(buf, MAX_FEATURE, f) || !strchr(buf, ','))
			break;

		el_ptr[0] = buf[0];
		responses.at<float>(i,0) = el_ptr[0];
		char* ptr;
		ptr = buf+2;
		for (int j=1; j<=VAR_COUNT; j++)
		{
			int n = 0;
			sscanf(ptr, "%f%n", el_ptr + j, &n);
			ptr += n + 1;
			data.at<float>(i, j-1) = el_ptr[j];
		}
	}
	fclose(f);
	delete el_ptr;
}

int main()
{
	txtfileRead("E:\\360YPan\\OpenCV\\OpenCV_Github\\ML\\source\\randomforest\\letter-recognition.data");
	getchar();
	return 0;
}