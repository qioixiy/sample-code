//显示图像文件
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    const char *pstrImageName = "001.jpg";
	const char *pstrWindowsTitle = "http://blog.csdn.net/MoreWindows";
	
	//从文件中读取图像
	IplImage *pImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
	
	//创建窗口
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);
	
	//在指定窗口中显示图像
	cvShowImage(pstrWindowsTitle, pImage);
	
	//等待按键事件
	cvWaitKey();
	
	cvDestroyWindow(pstrWindowsTitle);
	cvReleaseImage(&pImage);
	return 0;
}
