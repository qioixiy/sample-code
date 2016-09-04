#define assert(x)

extern "C" {
#include "libavutil/avstring.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/avassert.h"
#include "libavutil/time.h"
#include "libavutil/opt.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavcodec/avfft.h"

#include "common/createBmp/createBmp.h"

extern AVCodecContext	*pCodecCtx;
extern AVFrame	*pFrame;

void convertAndSaveAsBmp()
{
	int iResult = 0;
	
    int width = pCodecCtx->width;
    int height = pCodecCtx->height;
	//* 将YUV420P转换成RGB32.  
    SwsContext* pSwsCxt = sws_getContext(width,  
     height,  
     PIX_FMT_YUV420P,  
     width,  
     height,  
     PIX_FMT_RGB32,  
     SWS_BILINEAR, NULL, NULL, NULL);  
    uint8_t *rgb_data = static_cast<uint8_t*>(av_malloc(width*height*4));  
    uint8_t *rgb_src[3]= {rgb_data, NULL, NULL};  
    int rgb_stride[3]={4*width, 0, 0};  
    assert(pSwsCxt);  
    iResult = sws_scale(pSwsCxt, pFrame->data, pFrame->linesize,  
     0, height, rgb_src, rgb_stride);  
    assert(iResult == height);  
  
    /* {{ 测试代码,RGB32,YUV420之间的转换.  
    //* 将RGB32转换为YUV420P  
    AVFrame* pYUVFrm = alloc_picture(PIX_FMT_YUV420P, width, height);  
    SwsContext* pSwsCxtYUV = sws_getContext(width, height, PIX_FMT_RGB32,  
     width, height,  
     PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);//* 注意Flag的值.  
    iResult = sws_scale(pSwsCxtYUV, rgb_src, rgb_stride,  
     0, height, pYUVFrm->data, pYUVFrm->linesize);  
    assert(iResult == height);  
      
    //* 再转换成RGB32  
    ::memset(rgb_data, 0, width*height*4);  
    iResult = sws_scale(pSwsCxt, pYUVFrm->data, pYUVFrm->linesize,  
     0, height, rgb_src, rgb_stride);  
    assert(iResult == height);  
    //* }} */  
    char *sz = "out.bmp";
    CreateBmp(sz, rgb_data, width, height, 32);  
    ::memset(rgb_data, 0, width*height*4);  
    av_freep(&rgb_data);  
  
    //* 注意SwsContext必须用这个函数释放.  
    sws_freeContext(pSwsCxt); 
}
}