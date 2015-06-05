#pragma warning(disable:4996)

#include <string>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>	// Gaussian Blur
#include <opencv2/core/core.hpp>		// Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>	// OpenCV window I/O

#include <Windows.h>
#include <tchar.h>
#include "GlobalStruct.h"
#include "CBackgroundModel.h"

using namespace std;
using namespace cv;

#define MAX_THREAD		10		//线程数量

void ComputeROI(Rect& rectROI, Rect rectImage, int iStartPoint = 1)
{
	rectROI.x = rectImage.x - rectROI.width / 2;
	rectROI.y = rectImage.y - rectROI.height / 2;
	
	if (rectROI.x < iStartPoint)
	{
		rectROI.width = rectROI.width + rectROI.x - iStartPoint;
		rectROI.x = iStartPoint;
	}
	if (rectROI.y < iStartPoint)
	{
		rectROI.height = rectROI.height + rectROI.y - iStartPoint;
		rectROI.y = iStartPoint;
	}
	if (rectROI.x + rectROI.width >= rectImage.width)
	{
		rectROI.width += (rectImage.width - rectROI.x - rectROI.width);
	}
	if (rectROI.y + rectROI.height >= rectImage.height)
	{
		rectROI.height += (rectImage.height - rectROI.y - rectROI.height);
	}
}

// 前景权重矩阵计算
void CalculateForegroundWeight(Mat& imgForegroundWeight, Mat& imgForeground)
{
	for (int ii = 0; ii < imgForeground.rows; ii++)
	{
		for (int jj = 0; jj < imgForeground.cols; jj++)
		{
			// 对所有前景像素进行加权
			int iWeight = 0;
			if (*(imgForeground.data + imgForeground.step.buf[0] * ii + imgForeground.step.buf[1] * jj) == 255)
			{
				if (ii > 0 && jj > 0 && *(imgForeground.data + imgForeground.step.buf[0] * (ii - 1) + imgForeground.step.buf[1] * (jj - 1)) == 0)
				{
					iWeight++;
				}
				if (ii > 0 && *(imgForeground.data + imgForeground.step.buf[0] * (ii - 1) + imgForeground.step.buf[1] * jj) == 0)
				{
					iWeight++;
				}
				if (ii > 0 && jj < (imgForeground.cols - 1) && *(imgForeground.data + imgForeground.step.buf[0] * (ii - 1) + imgForeground.step.buf[1] * (jj + 1)) == 0)
				{
					iWeight++;
				}
				if (jj > 0 && *(imgForeground.data + imgForeground.step.buf[0] * ii + imgForeground.step.buf[1] * (jj - 1)) == 0)
				{
					iWeight++;
				}
				if (jj < (imgForeground.cols - 1) && *(imgForeground.data + imgForeground.step.buf[0] * ii + imgForeground.step.buf[1] * (jj + 1)) == 0)
				{
					iWeight++;
				}
				if (ii < (imgForeground.rows - 1) && jj > 0 && *(imgForeground.data + imgForeground.step.buf[0] * (ii + 1) + imgForeground.step.buf[1] * (jj - 1)) == 0)
				{
					iWeight++;
				}
				if (ii < (imgForeground.rows - 1) && *(imgForeground.data + imgForeground.step.buf[0] * (ii + 1) + imgForeground.step.buf[1] * jj) == 0)
				{
					iWeight++;
				}
				if (ii < (imgForeground.rows - 1) && jj < (imgForeground.cols - 1) && *(imgForeground.data + imgForeground.step.buf[0] * (ii + 1) + imgForeground.step.buf[1] * (jj + 1)) == 0)
				{
					iWeight++;
				}
				*(imgForegroundWeight.data + imgForegroundWeight.step.buf[0] * ii + imgForegroundWeight.step.buf[1] * jj) = iWeight;
			}
		}
	}
}

DWORD __stdcall ThreadGetForeground(LPVOID pParam)
{
	SParamThreadUpdateModel* param = (SParamThreadUpdateModel*)pParam;
	Mat* pImgIntegral = param->pImgIntegral;
	Mat* pImgForeground = param->pImgForeground;
	Mat* pImgBackground = param->pImgBackground;
	Mat* pImgFrame = param->pImgFrame;
	int iHeight = param->iHeight;
	int iRowIndex = param->iRowIndex;
	CBackgroundModel** classMatBM = param->classMatBM;

	for (int ii = ((iRowIndex == 0) ? 1 : iRowIndex); ii < iRowIndex + iHeight; ii++)
	{
		for (int jj = 1; jj < pImgIntegral->cols; jj++)
		{
			//if (classMatBM[ii-1][jj-1].UpdateModel(*pImgIntegral))
			//{
			//	Rect rectROI;
			//	rectROI.width = WIDTH_ZONE / 2;
			//	rectROI.height = HEIGHT_ZONE / 2;
			//	ComputeROI(rectROI, Rect(jj - 1, ii - 1, pImgForeground->cols, pImgForeground->rows), 0);

			//	for (int x = rectROI.x; x < rectROI.x + rectROI.width; x++)
			//	{
			//		for (int y = rectROI.y; y < rectROI.y + rectROI.height; y++)
			//		{
			//			*(pImgForeground->data + pImgForeground->step.buf[0] * y + pImgForeground->step.buf[1] * x) += 255 * 4 / (WIDTH_ZONE * HEIGHT_ZONE);
			//		}
			//	}
			//}
			if (classMatBM[ii-1][jj-1].GetForeground(*pImgIntegral))
			{
				*(pImgForeground->data + pImgForeground->step.buf[0] * (ii - 1) + pImgForeground->step.buf[1] * (jj - 1)) = 255;
			}
			else
			{
				//// 标出最小P2M距离比较小的点
				//if (classMatBM[ii-1][jj-1].m_iDistNow < 1)
				//{
				//	*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1)) = 255;
				//	*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1) + 1) = 0;
				//	*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1) + 2) = 0;
				//}

#ifndef NO_BACKGROUND_RECONSTRUCTION
				classMatBM[ii-1][jj-1].m_iDistArrBuff[classMatBM[ii-1][jj-1].m_iColorArrBuffIndex] = classMatBM[ii-1][jj-1].m_iDistNow;

				classMatBM[ii-1][jj-1].m_colorArrBuff[classMatBM[ii-1][jj-1].m_iColorArrBuffIndex].b = 
					*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1));
				classMatBM[ii-1][jj-1].m_colorArrBuff[classMatBM[ii-1][jj-1].m_iColorArrBuffIndex].g = 
					*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1) + 1);
				classMatBM[ii-1][jj-1].m_colorArrBuff[classMatBM[ii-1][jj-1].m_iColorArrBuffIndex].r = 
					*(pImgFrame->data + pImgFrame->step.buf[0] * (ii - 1) + pImgFrame->step.buf[1] * (jj - 1) + 2);
				classMatBM[ii-1][jj-1].m_iColorArrBuffIndex++;
				if (classMatBM[ii-1][jj-1].m_iColorArrBuffIndex >= LENGTH_COLOR_BUFF)
				{
					classMatBM[ii-1][jj-1].m_iColorArrBuffIndex = 0;
				}

				//classMatBM[ii-1][jj-1].AverageBkColor();
				//classMatBM[ii-1][jj-1].MiddleBkColor();
				classMatBM[ii-1][jj-1].MinP2MBkBkColor(*pImgIntegral);

				*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1)) = 
					classMatBM[ii-1][jj-1].m_colorBkNow.b;
				*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1) + 1) = 
					classMatBM[ii-1][jj-1].m_colorBkNow.g;
				*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1) + 2) = 
					classMatBM[ii-1][jj-1].m_colorBkNow.r;
#endif
			}
		}
	}

	return 0;
}

DWORD __stdcall ThreadUpdateModel(LPVOID pParam)
{
	SParamThreadUpdateModel* param = (SParamThreadUpdateModel*)pParam;
	Mat* pImgIntegral = param->pImgIntegral;
	Mat* pImgForeground = param->pImgForeground;
	Mat* pImgBackground = param->pImgBackground;
	Mat* pImgFrame = param->pImgFrame;
	int iHeight = param->iHeight;
	int iRowIndex = param->iRowIndex;
	CBackgroundModel** classMatBM = param->classMatBM;
	Mat* pImgForegroundWeight = param->pImgForegroundWeight;

	for (int ii = ((iRowIndex == 0) ? 1 : iRowIndex); ii < iRowIndex + iHeight; ii++)
	{
		for (int jj = 1; jj < pImgIntegral->cols; jj++)
		{
			if (*(pImgForeground->data + pImgForeground->step.buf[0] * (ii - 1) + pImgForeground->step.buf[1] * (jj - 1)) == 0)
			{
				classMatBM[ii-1][jj-1].UpdateModel(*pImgIntegral, *pImgForegroundWeight);
				/*if (classMatBM[ii-1][jj-1].UpdateModel(*pImgIntegral, *pImgForegroundWeight))
				{
					*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1)) = 255;
					*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1) + 1) = 0;
					*(pImgBackground->data + pImgBackground->step.buf[0] * (ii - 1) + pImgBackground->step.buf[1] * (jj - 1) + 2) = 0;
				}*/
			}
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	// 打开源
	bool bIsSourceVideo = false;		//数据来源是否是视频
	VideoCapture captSource;
	long START_FRM;
	char cImgSourceHead[MAX_PATH];
	char cImgSourceTail[MAX_PATH];
	bool bName4 = true;

	if (argc == 2)
	{
		bIsSourceVideo = true;		//数据来源是否是视频
		captSource.open(argv[1]);
		START_FRM = 2;		//开始帧序号
	}
	else
	{
		#if SCENE == 1
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/QQDownload/CityRoad/CityRoad_");
			strcpy(cImgSourceTail, ".bmp");
		#elif SCENE == 2
			START_FRM = 1000;		//开始帧序号
			strcpy(cImgSourceHead, "I:/P2M论文实验用数据库/ICME论文数据库/Airport/Airport/airport");
			strcpy(cImgSourceTail, ".bmp");
		#elif SCENE == 3
			START_FRM = 1000;		//开始帧序号
			strcpy(cImgSourceHead, "G:/QQDownload/Airport/airport");
			strcpy(cImgSourceTail, ".bmp");
		#elif SCENE == 4
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/背景建模数据库/BMC/111_png/input/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#elif SCENE == 5
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/背景建模数据库/BMC/511_png/input/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#elif SCENE == 6
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/背景建模数据库/BMC/121_png/input/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#elif SCENE == 7
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/背景建模数据库/BMC/521_png/input/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#elif SCENE == 8
			START_FRM = 365000;		//开始帧序号
			strcpy(cImgSourceHead, "I:/理光人群监控/数据/TYZX/Color/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#elif SCENE == 9
			START_FRM = 1;		//开始帧序号
			strcpy(cImgSourceHead, "G:/背景建模数据库/BMC/421_png/input/");
			strcpy(cImgSourceTail, ".png");
			bName4 = false;
		#endif
	}

	char cImgSource[MAX_PATH];
	//char cCurExeDir[MAX_PATH+1]; 
	//GetModuleFileName(NULL, (LPWSTR)cCurExeDir, MAX_PATH);
//	(_tcsrchr(cCurExeDir, _T('\\')))[0] = '\0';

 	if (!CreateDirectory((LPCWSTR)_T("./fg"), NULL))
	{
		cout << "创建前景目录失败！" << endl;
	}
	if (!CreateDirectory((LPCWSTR)_T("./bg"), NULL))
	{
		cout << "创建背景目录失败！" << endl;
	}
	if (!CreateDirectory((LPCWSTR)_T("./vd"), NULL))
	{
		cout << "创建录像目录失败！" << endl;
	}
	
#ifndef SAVE_PIC
	// 显示窗口
	namedWindow("Video", CV_WINDOW_AUTOSIZE);
	namedWindow("Foreground", CV_WINDOW_AUTOSIZE);
#endif

	// 循环处理
	char cFlag = 0;
	long cntFrm = START_FRM;
	Mat imgFrame;		//源图片
	Mat imgFrameGray;		//源图像的灰度图像
	Mat imgIntegral;		//积分图
	Mat imgForeground;		//前景二值图
	Mat imgBackground;		//恢复出来的背景图
	Mat imgForegroundWeight;		//前景权重二值图
	if (bIsSourceVideo)
	{
		captSource >> imgFrame;
	}
	else
	{
		if (bName4)
		{
			sprintf(cImgSource, "%s%ld%s", cImgSourceHead, cntFrm, cImgSourceTail);
		}
		else
		{
			sprintf(cImgSource, "%s%ld%s", cImgSourceHead, cntFrm, cImgSourceTail);
		}
		imgFrame = imread(cImgSource);
	}
	imgForeground = Mat::zeros(imgFrame.rows, imgFrame.cols, CV_8UC1);
	imgFrame.copyTo(imgBackground);
	imgFrameGray = Mat::zeros(imgFrame.rows, imgFrame.cols, CV_8UC1);
	imgIntegral = Mat::zeros(imgFrame.rows + 1, imgFrame.cols + 1, CV_32FC1);
	//imgForegroundWeight = Mat::zeros(imgFrame.rows, imgFrame.cols, CV_8UC1);

//	cout << sizeof(CBackgroundModel) << " " << sizeof(int) << endl;
	CBackgroundModel** classMatBM = new CBackgroundModel*[imgFrame.rows];		//背景模型
	for (int ii = 0; ii < imgFrame.rows; ii++)
	{
		classMatBM[ii] = new CBackgroundModel[imgFrame.cols];
		for (int jj = 0; jj < imgFrame.cols; jj++)
		{
			Rect rectROI;
			rectROI.width = WIDTH_ZONE;
			rectROI.height = HEIGHT_ZONE;
			ComputeROI(rectROI, Rect(jj, ii, imgFrame.cols, imgFrame.rows), 0);
			classMatBM[ii][jj].InitInfo(classMatBM, jj, ii, rectROI);
		}
	}

	//CBackgroundModel::rows = imgFrame.rows;
	//CBackgroundModel::cols = imgFrame.cols;

	while (!imgFrame.empty())
	{
		cout << cntFrm << endl;
		
		cvtColor(imgFrame, imgFrameGray, CV_BGR2GRAY);

/*		fprintf(fid, "%d ", *(imgFrameGray.data + imgFrameGray.step.buf[0] * 201 + imgFrameGray.step.buf[1] * 198));
		// 获取新的一帧
		cntFrm++;
		if (bIsSourceVideo)
		{
			captSource >> imgFrame;
		}
		else
		{
			sprintf(cImgSource, "%s%04d.bmp", cImgSourceHead, cntFrm);
			imgFrame = imread(cImgSource);
		}	//*/

		// 积分图
		integral(imgFrameGray, imgIntegral, CV_32F);

		// 开始算法
		if (cntFrm == START_FRM)
		{
			for (int ii = 1; ii < imgIntegral.rows; ii++)
			{
				for (int jj = 1; jj < imgIntegral.cols; jj++)
				{
					// 初始化背景模型
					Rect rectROI;
					rectROI.width = WIDTH_ZONE;
					rectROI.height = HEIGHT_ZONE;
					ComputeROI(rectROI, Rect(jj, ii, imgIntegral.cols, imgIntegral.rows));
					if (rectROI.width > 0 && rectROI.height > 0)
					{
 						classMatBM[ii-1][jj-1].InitModel(imgIntegral, rectROI);
					}
				}
			}
		}
		else
		{
			HANDLE hThread[MAX_THREAD];
			int iDivision = imgIntegral.rows / MAX_THREAD;		//将图像分为10块，供10个线程同时处理
			SParamThreadUpdateModel structParamThreadUpdateModel[MAX_THREAD];

			// 前景分割
			for (int ii = 0; ii < MAX_THREAD; ii++)
			{
				structParamThreadUpdateModel[ii].pImgIntegral = &imgIntegral;
				structParamThreadUpdateModel[ii].pImgForeground = &imgForeground;
				structParamThreadUpdateModel[ii].pImgBackground = &imgBackground;
				structParamThreadUpdateModel[ii].pImgFrame = &imgFrame;
				structParamThreadUpdateModel[ii].iHeight = (ii == MAX_THREAD - 1) ? (iDivision + imgFrame.rows % MAX_THREAD) : iDivision;
				structParamThreadUpdateModel[ii].iRowIndex = ii * iDivision + 1;
				structParamThreadUpdateModel[ii].classMatBM = classMatBM;
				
				hThread[ii] = CreateThread(NULL, 0, ThreadGetForeground, structParamThreadUpdateModel + ii, 0, 0);
				if (hThread[ii] == NULL) 
				{
					throw exception("Failed to create thread for classification");
				}
			}

			// windowsAPI函数，可以等待几乎所有内核对象
			WaitForMultipleObjects(MAX_THREAD, hThread , TRUE, INFINITE);

			// 背景修复中的空间平滑
			for (int ii = 0; ii < imgFrame.rows; ii++)
			{
				for (int jj = 0; jj < imgFrame.cols; jj++)
				{
					if (classMatBM[ii][jj].m_bSmooth)
					{
						*(imgBackground.data + imgBackground.step.buf[0] * ii + imgBackground.step.buf[1] * jj) = 
							*(imgBackground.data + imgBackground.step.buf[0] * classMatBM[ii][jj].m_pointSoureSmooth.y + imgBackground.step.buf[1] * classMatBM[ii][jj].m_pointSoureSmooth.x);
						*(imgBackground.data + imgBackground.step.buf[0] * ii + imgBackground.step.buf[1] * jj + 1) = 
							*(imgBackground.data + imgBackground.step.buf[0] * classMatBM[ii][jj].m_pointSoureSmooth.y + imgBackground.step.buf[1] * classMatBM[ii][jj].m_pointSoureSmooth.x + 1);
						*(imgBackground.data + imgBackground.step.buf[0] * ii + imgBackground.step.buf[1] * jj + 2) = 
							*(imgBackground.data + imgBackground.step.buf[0] * classMatBM[ii][jj].m_pointSoureSmooth.y + imgBackground.step.buf[1] * classMatBM[ii][jj].m_pointSoureSmooth.x + 2);
					}
				}
			}

			// 前景权重图计算
			//memset(imgForegroundWeight.data, 0, imgForegroundWeight.step.buf[0] * imgForegroundWeight.rows * sizeof(uchar));
			//CalculateForegroundWeight(imgForegroundWeight, imgForeground);

			// 模型更新
			for (int ii = 0; ii < MAX_THREAD; ii++)
			{
				structParamThreadUpdateModel[ii].pImgForegroundWeight = &imgForegroundWeight;

				hThread[ii] = CreateThread(NULL, 0, ThreadUpdateModel, structParamThreadUpdateModel + ii, 0, 0);
				if (hThread[ii] == NULL) 
				{
					throw exception("Failed to create thread for classification");
				}
			}

			// windowsAPI函数，可以等待几乎所有内核对象
			WaitForMultipleObjects(MAX_THREAD, hThread , TRUE, INFINITE);

			//// 最大距离更新
			//for (int ii = 0; ii < imgFrame.rows; ii++)
			//{
			//	for (int jj = 0; jj < imgFrame.cols; jj++)
			//	{
			//		if (classMatBM[ii][jj].m_bIsRefreshModel)
			//		{
			//			classMatBM[ii][jj].ReplaceMaxFeature();
			//			classMatBM[ii][jj].m_bIsRefreshModel = false;
			//		}
			//	}
			//}

			//for(int i=0; i< MAX_THREAD; i++)
			//{
			//	//关闭线程
			//	CloseHandle(hThread[i]);
			//}
		}

		//// 后期处理
		//erode(imgForeground, imgForeground, Mat(3, 3, CV_8U));
		//dilate(imgForeground, imgForeground, Mat(3, 3, CV_8U));
		medianBlur(imgForeground, imgForeground,9);

#ifdef SAVE_PIC
#ifndef NO_BACKGROUND_RECONSTRUCTION
		// 保存结果
		char str[MAX_PATH];
		sprintf(str, "./fg/fg_%04d.png", cntFrm);
		imwrite(str, imgForeground);
		sprintf(str, "./bg/bg_%04d.png", cntFrm);
		imwrite(str, imgBackground);
		sprintf(str, "./vd/vd_%04d.png", cntFrm);
		imwrite(str, imgFrame);
#endif
#endif

#ifndef SAVE_PIC
		// 显示效果
		imshow("Video", imgFrame);
		imshow("Foreground", imgForeground);

#ifndef NO_BACKGROUND_RECONSTRUCTION
		imshow("Background", imgBackground);
#endif
#endif

		// 获取新的一帧
		cntFrm++;
		if (bIsSourceVideo)
		{
			captSource >> imgFrame;
		}
		else
		{
			if (bName4)
			{
				sprintf(cImgSource, "%s%ld%s", cImgSourceHead, cntFrm, cImgSourceTail);
			}
			else
			{
				sprintf(cImgSource, "%s%ld%s", cImgSourceHead, cntFrm, cImgSourceTail);
			}
			imgFrame = imread(cImgSource);
		}
		memset(imgForeground.data, 0, imgForeground.step.buf[0] * imgForeground.rows * sizeof(uchar));

		// 暂停和退出控制
		cFlag = cvWaitKey(2);
		if(cFlag == 32)
		{
			cFlag = cvWaitKey(2);
			while(cFlag != 27 && cFlag != 32)
				cFlag = cvWaitKey(2);
		}
		if(cFlag == 27)
			break;
	}
	
	for (int ii = 0; ii < imgFrame.rows; ii++)
	{
		delete[] classMatBM[ii];
		classMatBM[ii] = NULL;
	}
	delete[] classMatBM;
	classMatBM = NULL;	

	return 0;
}