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

#include "common/yuv/yuv.h"

static void register_atexit()
{
	atexit(SDL_Quit);
}


AVFormatContext	*pFormatCtx;
AVCodecContext	*pCodecCtx;
AVCodec			*pCodec;
AVFrame	*pFrame;
char *filepath = "butterfly.h264";
int videoindex = -1;

int main_ffmpeg_init(void)
{
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	if(avformat_open_input(&pFormatCtx,filepath,NULL,NULL)!=0) {
		printf("can not open the file %s\n", filepath);
		return -1;
	}
	if(avformat_find_stream_info(pFormatCtx, 0) < 0) {
		printf("Couldn't find stream information.\n");
		return -1;
	}
	int i;	
	for(i=0; i<pFormatCtx->nb_streams; i++) {
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
			videoindex = i;
			break;
		}
	}
	if(videoindex == -1) {
		printf("Didn't find a video stream.\n");
		return -1;
	}
#if 0
	pCodecCtx=pFormatCtx->streams[videoindex]->codec;
	pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
#else
	pCodec=avcodec_find_decoder(AV_CODEC_ID_H264);
	pCodecCtx = avcodec_alloc_context3(pCodec);
	pCodecCtx->codec_id = AV_CODEC_ID_H264;
	pCodecCtx->width = 720;
	pCodecCtx->height = 576;
	pCodecCtx->pix_fmt=PIX_FMT_YUV420P;
#endif

	if(pCodec==NULL) {
		printf("Codec not found.\n");
		return -1;
	}
	AVDictionary *opts = NULL;

	if(avcodec_open2(pCodecCtx, pCodec, &opts)<0) {
		printf("Could not open codec.\n");
		return -1;
	}

	pFrame = avcodec_alloc_frame();
	
	return 0;
}

static void main_ffmpeg_exit(void)
{
	av_free(pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}

int main_loop(void)
{
	int ret, got_picture;
	int y_size = pCodecCtx->width * pCodecCtx->height;

	AVPacket *packet=(AVPacket *)malloc(sizeof(AVPacket));
	av_new_packet(packet, y_size);
#if 0
	while(av_read_frame(pFormatCtx, packet)>=0)	{
#else
	extern void h264_packet_queue_init(int size);
	extern AVPacket *h264_packet_queue_get();
	h264_packet_queue_init(1000);
	while(packet = h264_packet_queue_get())	{
		printf("get packet\n");
#endif
#define _DEBUG
#ifdef _DEBUG
		printf("packet=0x%x\n", packet);
		uint8_t *buf = packet->data;
		printf("packet->data=0x%x\n", buf);
		printf("avpkt:0x%02x%02x%02x%02x,%02x%02x%02x%02x,\tsize=0x%x\n",
			buf[0], buf[1], buf[2], buf[3],buf[4], buf[5], buf[6], buf[7],
			packet->size);
		printf("packet->stream_index=%d, videoindex=%d\n", packet->stream_index, videoindex);
#endif
		if(packet->stream_index==videoindex) {
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if(ret < 0) {
				printf("decode error...\n");
				return -1;
			}
			if(got_picture)	{
			    save_yuvfile(pFrame, pCodecCtx);
				show_yuvdata(pFrame, pCodecCtx);
				convertAndSaveAsBmp();
				
			    SDL_Delay(40);//25
			    //SDL事件处理
			    SDL_Event sdl_event;
			    while(SDL_PollEvent(&sdl_event)) {
				    switch(sdl_event.type) {
				    default: //continue
				    case SDL_KEYDOWN:
					    break;
				    case SDL_KEYUP:
					    if(sdl_event.key.keysym.sym == SDLK_q) {
						    return 0;
					    }
					    break;
				    case SDL_QUIT:
					    return 0;
				    }
			    }	
			}
		}
		//av_free_packet(packet);
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	register_atexit();

	if (argc !=1) {
	    filepath = argv[1];
	}
	
	main_ffmpeg_init();
	main_sdl_init(pCodecCtx->width, pCodecCtx->height);

	printf("file info----------------------------------------\n");
	av_dump_format(pFormatCtx,0,filepath,0);
	printf("-------------------------------------------------\n");
	
	main_loop();

	main_ffmpeg_exit();

	getchar();
	return 0;
}
