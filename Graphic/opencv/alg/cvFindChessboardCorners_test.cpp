// refs: https://blog.csdn.net/h532600610/article/details/51800488

#include <iostream>
#include <cv.h>
#include <cv.hpp>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

int main( )
{
    cout<<"Draw Chess OpenCV!"<<endl;
    const char* filename="in.png";
    const char* filename2="out.png";
    IplImage* imgRGB = cvLoadImage(filename);
    IplImage* imgGrey = cvLoadImage(filename,CV_LOAD_IMAGE_GRAYSCALE);

    if (imgGrey==NULL){//image validation
        cout<< "No valid image input."<<endl;
        char c=getchar();
        return 1;
    }

    // find chessboard corners
    int corner_row=7;           //interior number of row corners.(this can be countered by fingers.)
    int corner_col=7;           //interior number of column corners.
    int corner_n=corner_row*corner_col;
    CvSize pattern_size=cvSize(corner_row,corner_col);
    // CvPoint2D32f* corners=new CvPoint2D32f[corner_n];
    CvPoint2D32f corners[49];
    int corner_count;

    int found=cvFindChessboardCorners(//returning non-zero means sucess.
        imgGrey,// 8-bit single channel greyscale image.
        pattern_size,//how many INTERIOR corners in each row and column of the chessboard.
        corners,//an array where the corner locations can be recorded.
        &corner_count,// optional, if non-NULL, its a point to an integer where the nuber of corners found can be recorded.
        // CV_CALIB_CB_ADAPTIVE_THRESH|CV_CALIB_CB_FILTER_QUADS// check page 382-383.
        0
                                      );
    cout << "corner_count=" << corner_count;

    //-------Draw the corner pattern-------
    cvDrawChessboardCorners(
        imgRGB,
        pattern_size,
        corners,
        corner_count,
        found
                            );
    cvSaveImage(filename2,imgRGB);
    //to summary a bit of findings.
    cout << "found=" << found << endl;
    cout << "x="<<corners[1].x << ",y=" <<corners[1].y << endl;

    cvNamedWindow("Find and Draw ChessBoard", 0);
    cvShowImage("Find and Draw ChessBoard", imgRGB);

    cvWaitKey(0);

    cvReleaseImage(&imgGrey);
    cvReleaseImage(&imgRGB);
    cvDestroyWindow("Find and Draw ChessBoard");

    return 0;
}
