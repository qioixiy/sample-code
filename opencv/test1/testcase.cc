#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

TEST(opencv, capture_device)
{
    std::string windowName = "opencv_capture_camera";

    cv::VideoCapture capture;
    capture.open(0);            //open 根据编号打开摄像头

    if (!capture.isOpened()) {
        std::cout << "open video device failed" << std::endl;
        return;
    }

    cv::namedWindow(windowName);

    int frame_num = 600;

    cv::Mat frame;
    for (int i = 0; i < frame_num; ++i) {
        //capture >> frame;
        capture.read(frame);

        imshow(windowName, frame);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cv::destroyWindow(windowName);
    capture.release();
}

void processIamge(Mat &frame)
{
    circle(frame,
           Point(cvRound(frame.cols / 2), cvRound(frame.rows / 2)),
           150, Scalar(0, 0, 255), 2, 8);
}

TEST(opencv, capture_device_process)
{
    std::string windowName = "opencv_capture_camera";

    cv::VideoCapture capture;
    capture.open(0);            //open 根据编号打开摄像头

    if (!capture.isOpened()) {
        std::cout << "open video device failed" << std::endl;
        return;
    }

    cv::namedWindow(windowName);

    int frame_num = 600;

    cv::Mat frame;
    for (int i = 0; i < frame_num; ++i) {
        //capture >> frame;
        capture.read(frame);

        processIamge(frame);

        imshow(windowName, frame);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cv::destroyWindow(windowName);
    capture.release();
}

void processIamgeMerge(Mat &frame, Mat &frame2,Mat &frame3, Mat &frame4,
                       Mat &frameDst)
{
    //frame.copyTo(frameDst);

    frameDst.create(Size(640, 480*4), CV_8UC3);
    frameDst = Scalar::all(0);

    frame.copyTo(frameDst(Rect(0, frame.rows*0, frame.cols, frame.rows)));
    frame2.copyTo(frameDst(Rect(0, frame.rows*1, frame.cols, frame.rows)));
    frame3.copyTo(frameDst(Rect(0, frame.rows*2, frame.cols, frame.rows)));
    frame4.copyTo(frameDst(Rect(0, frame.rows*3, frame.cols, frame.rows)));
}

TEST(opencv, capture_device_process_merge)
{
    std::string windowName = "opencv_capture_camera";

    cv::VideoCapture capture;
    capture.open(0);            //open 根据编号打开摄像头

    if (!capture.isOpened()) {
        std::cout << "open video device failed" << std::endl;
        return;
    }

    cv::namedWindow(windowName);

    int frame_num = 600;

    cv::Mat frame;
    for (int i = 0; i < frame_num; ++i) {
        capture >> frame;
        cv::Mat frame2;
        cv::Mat frameDst(Size(frame.cols, frame.rows), CV_8UC3);
        frame.copyTo(frame2);

        processIamgeMerge(frame, frame2, frame2, frame2, frameDst);

        imshow(windowName, frameDst);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cv::destroyWindow(windowName);
    capture.release();
}

TEST(opencv, capture_device_writer)
{
    VideoCapture capture(0);

    if (!capture.isOpened()) {
        std::cout << "open video device failed" << std::endl;
        return;
    }

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    VideoWriter writer("capture_writer_out.avi",
                       CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(640, 480));

    int count = 0;
    while (true) {
        Mat frame;
        capture >> frame;

        stringstream ss;
        ss << "frame:" << count++;
        putText(frame,
                ss.str(), Point(0, 40),
                CV_FONT_HERSHEY_SIMPLEX, 1., (255, 255, 0), 2);

        writer << frame;

        imshow("video", frame);
        if (cvWaitKey(30) == 'q') {
            break;
        }
    }
}

TEST(opencv, capture_file)
{
    std::string windowName = "opencv_capture_file";

    cv::VideoCapture capture;
    capture.open("test.mp4");

    if (!capture.isOpened()) {
        std::cout << "read video file failed!" << std::endl;
        return;
    }

    int frame_num = capture.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "total frame number is:" << frame_num << std::endl;

    cv::namedWindow(windowName);

    cv::Mat frame;
    for (int i = 0; i < frame_num - 1; ++i) {
        //capture >> frame;
        capture.read(frame);

        imshow(windowName, frame);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cv::destroyWindow(windowName);
    capture.release();
}

TEST(opencv, capture_file_show)
{
    IplImage *frame = NULL;
    CvCapture *capture = NULL;
    capture = cvCreateFileCapture("test.mp4");
    frame = cvQueryFrame(capture);
    cvNamedWindow("frame");

    while (frame) {
        cvShowImage("frame", frame);
        cvWaitKey(10000);
        std::cout << "Frame Grabbed." << std::endl;
        frame = cvQueryFrame(capture);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
