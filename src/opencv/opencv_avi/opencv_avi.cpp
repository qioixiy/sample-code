#include "highgui.h"
using namespace cv;
using namespace std;
 
int main()
{
    cvNamedWindow("example");
    CvCapture * capture = cvCreateFileCapture("vp31.avi");
    IplImage * frame;
    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame)break;
        cvShowImage("example",frame);
        char c = cvWaitKey(33);
        if(c==27) break;
    }
    cvReleaseCapture(&capture);
    cvDestroyWindow("example");
}
