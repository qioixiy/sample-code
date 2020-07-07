#ifndef _YUV_H_
#define _YUV_H_

void save_yuvfile(AVFrame* frame, AVCodecContext* avctx);
void show_yuvdata(AVFrame * frame, AVCodecContext* avctx);
void main_sdl_init(int width, int height);

#endif