//缩放图像文件
//By MoreWindows (http://blog.csdn.net/MoreWindows)
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    const char *pstrImageName = "001.jpg";
	const char *pstrSaveImageName = "001_resize.jpg";
	const char *pstrWindowsSrcTitle = "原图 (http://blog.csdn.net/MoreWindows)";
	const char *pstrWindowsDstTitle = "缩放图 (http://blog.csdn.net/MoreWindows)";

	double fScale = 0.314;            //缩放倍数
	CvSize czSize;                         //目标图像尺寸

	//从文件中读取图像
	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;

	//计算目标图像大小
	czSize.width = pSrcImage->width * fScale;
	czSize.height = pSrcImage->height * fScale;

	//创建图像并缩放
	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_AREA);

	//创建窗口
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsDstTitle, CV_WINDOW_AUTOSIZE);

	//在指定窗口中显示图像
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);
	cvShowImage(pstrWindowsDstTitle, pDstImage);

	//等待按键事件
	cvWaitKey();

	//保存图片
	cvSaveImage(pstrSaveImageName, pDstImage);

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsDstTitle);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDstImage);
	return 0;
}
