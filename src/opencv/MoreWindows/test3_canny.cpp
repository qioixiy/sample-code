//图像的Canny边缘检测
//By MoreWindows (http://blog.csdn.net/MoreWindows)
#include <opencv2/opencv.hpp>
using namespace std;

IplImage *g_pSrcImage, *g_pCannyImg;
const char *pstrWindowsCannyTitle = "边缘检测图(http://blog.csdn.net/MoreWindows)";
//cvCreateTrackbar的回调函数
void on_trackbar(int threshold)
{
//canny边缘检测
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowsCannyTitle, g_pCannyImg);
}
int main()
{
	const char *pstrImageName = "001.jpg";
	const char *pstrWindowsSrcTitle = "原图(http://blog.csdn.net/MoreWindows)";
	const char *pstrWindowsToolBar = "Threshold";

//从文件中载入图像的灰度图CV_LOAD_IMAGE_GRAYSCALE - 灰度图
	g_pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g_pSrcImage), IPL_DEPTH_8U, 1);

//创建窗口
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsCannyTitle, CV_WINDOW_AUTOSIZE);

//创建滑动条
	int nThresholdEdge = 1;
	cvCreateTrackbar(pstrWindowsToolBar, pstrWindowsCannyTitle, &nThresholdEdge, 100, on_trackbar);

//在指定窗口中显示图像
	cvShowImage(pstrWindowsSrcTitle, g_pSrcImage);
	on_trackbar(1);

//等待按键事件
	cvWaitKey();

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsCannyTitle);
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pCannyImg);
	return 0;
}
