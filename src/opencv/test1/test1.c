// test.cpp  

#include <stdio.h>
  
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>  
  
int main()  
{  
	CvCapture* capture = NULL;  
	IplImage* frame = NULL;  
	
	printf("will open camera./n");

	if( !(capture = cvCaptureFromCAM(-1)))  
	{  
		fprintf(stderr, "Can not open camera./n");  
		return -1;  
	} else {
		printf("open camera./n");  
	} 

	cvNamedWindow("video", 1);  
	
	while(frame = cvQueryFrame( capture ) )  
	{  
		cvShowImage("video", frame);  
	}  
	
	cvDestroyWindow("video");  
	cvReleaseCapture(&capture);  
	
	return 0;
}  
