#include <SDL/SDL.h>

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

#include "yuv.h"
SDL_Surface *pscreen;
SDL_Overlay *poverlay;


static FILE * out_yuv = NULL;

void main_sdl_init(int width, int height)
{
	//初始化SDL子系统
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to init SDL:%s", SDL_GetError());
		exit(2);
	}

	pscreen = SDL_SetVideoMode(width, height,24, SDL_SWSURFACE);
	if(pscreen == NULL) {
		printf("error at setvideomode");
		exit(3);
	}
	poverlay = SDL_CreateYUVOverlay(width,height,SDL_YV12_OVERLAY,pscreen);
	if(poverlay == NULL) {
		printf("error at ppoverlay");
		exit(4);
	}
}

//显示（弹出flip）screen surface到屏幕上 
static unsigned int flip(unsigned char * src, int width, int height) 
{ 
	unsigned char  *outy,*outu,*outv,*out_buffer,*op[3];
	SDL_Rect rect;

	rect.w = width;
	rect.h = height;
	rect.x = 0;
	rect.y = 0;
	out_buffer = src;
	SDL_LockSurface(pscreen);
	SDL_LockYUVOverlay(poverlay);
	outy = out_buffer;
	outu = out_buffer+width*height*5/4;
	outv = out_buffer+width*height;
	int y;
	for(y = 0; y < pscreen->h && y<poverlay->h; y++) {
		op[0]=poverlay->pixels[0]+poverlay->pitches[0]*y;
		op[1]=poverlay->pixels[1]+poverlay->pitches[1]*(y/2);
		op[2]=poverlay->pixels[2]+poverlay->pitches[2]*(y/2);   
		memcpy(op[0],outy+y*width,width);
		if(y%2 == 0) {
			memcpy(op[1],outu+width/2*y/2,width/2);
			memcpy(op[2],outv+width/2*y/2,width/2);   
		}
	}

	SDL_UnlockYUVOverlay(poverlay);
	SDL_UnlockSurface(pscreen);       
	SDL_DisplayYUVOverlay(poverlay, &rect);

	return 0;
} 

static void write_file(unsigned char *buf, int linesize, int xsize, int ysize,
					   FILE *f)
{
	int i = 0;
	for (; i < ysize; i++) {
		fwrite(buf + i * linesize, 1, xsize, f);
	}
}

void save_yuvfile(AVFrame* frame, AVCodecContext* avctx)
{	
	static unsigned int flag = 0;
	if (0 == flag) {
		flag = 1;
		char outfilename[20];
		sprintf(outfilename, "out_%dx%d.yuv", avctx->width, avctx->height);
		out_yuv = fopen(outfilename, "w");
	}
	
	write_file(frame->data[0], frame->linesize[0], avctx->width, avctx->height, out_yuv);//Y
	write_file(frame->data[1], frame->linesize[1], avctx->width/2, avctx->height/2, out_yuv);//U
	write_file(frame->data[2], frame->linesize[2], avctx->width/2, avctx->height/2, out_yuv);//V

}

void show_yuvdata(AVFrame * frame, AVCodecContext* avctx)
{
	static unsigned int flag = 0;
	static unsigned char *s_buf = NULL;

	if (0 == flag) {
		flag = 1;
		s_buf = malloc(avctx->width * avctx->height * 3/2);
	}

	unsigned char *buf = s_buf;
	int i, linesize, xsize, ysize;
	for (i = 0, linesize= frame->linesize[0], xsize = avctx->width, ysize = avctx->height;
		 i < ysize; i++ ) {
	    memcpy(buf +i * xsize, frame->data[0] + i * linesize,xsize);
	}
	buf = buf +i * xsize;

	for (i = 0, linesize= frame->linesize[1], xsize = avctx->width/2, ysize = avctx->height/2;
		 i < ysize; i++ ) {
	    memcpy(buf +i * xsize, frame->data[1] + i * linesize,xsize);
	}
	buf = buf +i * xsize;
	for (i = 0, linesize= frame->linesize[2], xsize = avctx->width/2, ysize = avctx->height/2;
		 i < ysize; i++ ) {
	    memcpy(buf +i * xsize, frame->data[2] + i * linesize,xsize);
	}

	flip(s_buf, avctx->width, avctx->height);
}