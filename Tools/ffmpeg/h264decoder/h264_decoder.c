#ifdef __cplusplus  
exter/n"C"{   
#endif   
    
#include "libavutil/imgutils.h"  
#include "libavutil/opt.h"  
#include "libavcodec/avcodec.h"  
#include "libavutil/mathematics.h"  
#include "libavutil/samplefmt.h"  
    
#ifdef __cplusplus  
}   
#endif   
    
#define INBUF_SIZE (4096)  
    
    
/*  
 * Video decoding example 
 */  
    
static  void pgm_save(unsigned char *buf, int  wrap, int xsize, int  ysize,   
					FILE*f)   
{   
    int i;   
	//buf += 64;  
    //fprintf(f,"P5n%d %dn%d/n",xsize,ysize,255);  
    for(i=0;i<ysize;i++)  
        fwrite(buf + i * wrap,1,xsize,f);  
}   
    
static  int  _find_head(unsigned char *buffer,int  len)   
{   
	int i;   
	int j;   
     
	for(i=512;i<len;i++)   
	{  
		if(buffer[i] == 0   
		   && buffer[i+1] == 0  
		   && buffer[i+2] == 0  
		   && buffer[i+3] == 1)  
			break;  
	}  
	if(i == len)   
		return 0;   
	if(i == 512)   
		return 0;   
	return i;   
}   
#define FILE_READING_BUFFER (1*1024*1024)  
static void build_avpkt(AVPacket *avpkt,FILE *fp)   
{   
#if 0   
	int len;   
	static unsigned  char buffer[INBUF_SIZE];   
	len =fread(buffer, 1, INBUF_SIZE, fp);  
	avpkt->data = buffer;  
	avpkt->size = len;  
#else   
	static unsigned  char buffer[1*1024*1024];   
	static int  readptr = 0;   
	static int  writeptr = 0;   
	int len,toread;   
    
	int nexthead;   
    
	if(writeptr - readptr < 200 * 1024)   
	{  
		memmove(buffer, &buffer[readptr], writeptr - readptr);  
		writeptr -= readptr;  
		readptr = 0;  
		toread = FILE_READING_BUFFER - writeptr;  
		len =fread(&buffer[writeptr], 1, toread, fp);  
		writeptr += len;  
	}  
    
	nexthead = _find_head(&buffer[readptr], writeptr-readptr);  
	if(nexthead == 0)   
	{  
		printf("failed find next head.../n");  
		nexthead = writeptr - readptr;  
	}  
    
	avpkt->size = nexthead;  
	avpkt->data = &buffer[readptr];  
	readptr += nexthead;  
#endif   
}   
    
static void video_decode_example(const char *outfilename, const char *filename)   
{   
    AVCodec *codec;  
    AVCodecContext *c= NULL;  
    int frame, got_picture, len;   
    FILE*f, *fout;   
    AVFrame *picture;  
    uint8_t inbuf[INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];  
    char buf[1024];   
    AVPacket avpkt;  
    AVDictionary *opts;  
    
    av_init_packet(&avpkt);  
    
    /* set end of buffer to 0 (this ensures that no overreading happens for damaged mpeg streams) */  
    memset(inbuf + INBUF_SIZE, 0, FF_INPUT_BUFFER_PADDING_SIZE);  
    
    printf("Video decoding/n");  
    opts = NULL;  
    //av_dict_set(&opts, "b", "2.5M", 0);  
    /* find the mpeg1 video decoder */  
    codec = avcodec_find_decoder(CODEC_ID_H264);  
    if(!codec) {   
        fprintf(stderr,"codec not found/n");  
        exit(1);  
    }  
    
    c = avcodec_alloc_context3(codec);  
    picture= avcodec_alloc_frame();  
    
    if(codec->capabilities&CODEC_CAP_TRUNCATED)  
        c->flags|= CODEC_FLAG_TRUNCATED;/* we do not send complete frames */  
    
    /* For some codecs, such as msmpeg4 and mpeg4, width and height 
       MUST be initialized there because this information is not 
       available in the bitstream. */  
    
    /* open it */  
    if(avcodec_open2(c, codec, NULL) < 0) {   
        fprintf(stderr,"could not open codec/n");  
        exit(1);  
    }  
    
     
    fout=fopen(outfilename,"wb");  
    /* the codec gives us the frame size, in samples */  
    
    f =fopen(filename,"rb");   
    if(!f) {   
        fprintf(stderr,"could not open %s/n", filename);  
        exit(1);  
    }  
    
    frame = 0;  
    for(;;) {  
        //avpkt.size = fread(inbuf, 1, INBUF_SIZE, f);  
        build_avpkt(&avpkt, f);  
        if(avpkt.size == 0)   
            break;  
    
        /* NOTE1: some codecs are stream based (mpegvideo, mpegaudio) 
           and this is the only method to use them because you cannot 
           know the compressed data size before analysing it. 
   
           BUT some other codecs (msmpeg4, mpeg4) are inherently frame 
           based, so you must call them with all the data for one 
           frame exactly. You must also initialize 'width' and 
           'height' before initializing them. */  
    
        /* NOTE2: some codecs allow the raw parameters (frame size, 
           sample rate) to be changed at any frame. We handle this, so 
           you should also take care of it */  
    
        /* here, we use a stream based decoder (mpeg1video), so we 
           feed decoder and see if it could decode a frame */  
        //avpkt.data = inbuf;  
        while(avpkt.size > 0) {   
            len = avcodec_decode_video2(c, picture, &got_picture, &avpkt);  
            if(len < 0) {   
                fprintf(stderr,"Error while decoding frame %d/n", frame);  
                break;  
                //   exit(1);  
            }  
            if(got_picture) {   
                printf("saving frame %3d/n", frame);  
                fflush(stdout);  
    
                /* the picture is allocated by the decoder. no need to 
                   free it */  
                sprintf(buf, outfilename, frame);  
                pgm_save(picture->data[0], picture->linesize[0],  
                         c->width, c->height, fout);  
                pgm_save(picture->data[1], picture->linesize[1],  
                         c->width/2, c->height/2, fout);  
                pgm_save(picture->data[2], picture->linesize[2],  
                         c->width/2, c->height/2, fout);  
                frame++;  
            }  
            avpkt.size -= len;  
            avpkt.data += len;  
        }  
    }  
    
    /* some codecs, such as MPEG, transmit the I and P frame with a 
       latency of one frame. You must do the following to have a 
       chance to get the last frame of the video */  
    avpkt.data = NULL;  
    avpkt.size = 0;  
    len = avcodec_decode_video2(c, picture, &got_picture, &avpkt);  
    if(got_picture) {   
        printf("saving last frame %3d/n", frame);  
        fflush(stdout);  
    
        /* the picture is allocated by the decoder. no need to 
           free it */  
        sprintf(buf, outfilename, frame);  
        //pgm_save(picture->data[0], picture->linesize[0],  
		//       c->width, c->height, fout);  
		pgm_save(picture->data[0], picture->linesize[0],c->width, c->height, fout);  
		pgm_save(picture->data[1], picture->linesize[1],c->width/2, c->height/2, fout);  
		pgm_save(picture->data[2], picture->linesize[2],c->width/2, c->height/2, fout);  
    
		frame++;  
    }  
    
    fclose(f);  
	fclose(fout);  
    
    avcodec_close(c);  
    av_free(c);  
    av_free(picture);  
    printf("/n");  
}   
    
    
int main(int  argc, char* argv[])   
{   
	printf("hello world/n");  
	avcodec_register_all();  
	video_decode_example("output.yuv", "record.h264");  
	return 0;  
}
