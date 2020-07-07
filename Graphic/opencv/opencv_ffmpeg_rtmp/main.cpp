#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <highgui.hpp>
#include <imgproc.hpp>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

using namespace std;
using namespace cv;

const char* name = "example";

int main()
{
    // opencv
    cv::namedWindow(name);
    auto capture = cv::VideoCapture("vp31.avi");
    cv::Mat frame;

    // ffmpeg
    avcodec_register_all();
    av_register_all();
    avformat_network_init();
    SwsContext *vsc = NULL;
    AVFrame *yuv = NULL;
    AVCodecContext *vc = NULL;
    AVFormatContext *ic = NULL;

    while(1) {
        capture >> frame;
        cv::imshow(name, frame);
        char c = cv::waitKey(33);
        if (c=='q') break;
    }

    cv::destroyWindow(name);
}
