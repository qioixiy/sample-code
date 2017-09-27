// 详见《【OpenCV入门指南】第一篇 安装OpenCV》
// 地址： http://blog.csdn.net/morewindows/article/details/8225783

// 本文配套博客文章地址：
// http://blog.csdn.net/morewindows/article/details/8426318

// Haar特征检测 - 人脸识别
//By MoreWindows (http://blog.csdn.net/MoreWindows)
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
//#include <Windows.h>
using namespace std;
int main()
{
// 加载Haar特征检测分类器
// haarcascade_frontalface_alt.xml系OpenCV自带的分类器 下面是我机器上的文件路径
	const char *pstrCascadeFileName = "./haarcascade_frontalface_alt2.xml";//"G:\OpenCV\opencv\data\haarcascades\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);

// 载入图像
	const char *pstrImageName = "002.jpg";
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);

	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

// 人脸识别与标记
	if (pHaarCascade != NULL)
	{
		CvScalar FaceCirclecolors[] = 
			{
				{{0, 0, 255}},
				{{0, 128, 255}},
				{{0, 255, 255}},
				{{0, 255, 0}},
				{{255, 128, 0}},
				{{255, 255, 0}},
				{{255, 0, 0}},
				{{255, 0, 255}}
			};

		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage);
// 识别
		//DWORD dwTimeBegin, dwTimeEnd;
		//dwTimeBegin = GetTickCount();
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);
		//dwTimeEnd = GetTickCount();

		//printf("人脸个数: %d   识别用时: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);

// 标记
		for(int i = 0; i <pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width * 0.5));
			center.y = cvRound((r->y + r->height * 0.5));
			radius = cvRound((r->width + r->height) * 0.25);
			cvCircle(pSrcImage, center, radius, FaceCirclecolors[i % 8], 2);
		}
		cvReleaseMemStorage(&pcvMStorage);
	}

	const char *pstrWindowsTitle = "人脸识别 (http://blog.csdn.net/MoreWindows)";
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsTitle, pSrcImage);

	cvWaitKey(0);

	cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pGrayImage);
	return 0;
}

