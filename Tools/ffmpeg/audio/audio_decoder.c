#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#ifdef __cplusplus
}
#endif

int main(char arg,char *argv[])
{
    //const char    *url = "file:in.mp3";
    const char *url = argv[1];

    av_register_all();

    AVFormatContext *oc = NULL;
    AVOutputFormat *fmt;
    AVCodecContext *pInCodecCtx = NULL;

    int ret = avformat_alloc_output_context2(&oc, NULL, NULL, url);
    if (ret < 0) {
        printf("av_open_input_file error\n");
    }
    fmt = oc->oformat;

    AVDictionary **options;
    if (avformat_find_stream_info(oc, options) < 0)
        printf("av_find_stream_info error\n");

    unsigned int j;
    // Find the first audio stream
    int audioStream = -1;
    for (j=0; j<oc->nb_streams; j++) {
        if (oc->streams[j]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioStream = j;
            break;
        }
    }
    if (audioStream == -1) {
        printf("input file has no audio stream\n");
        return 0; // Didn't find a audio stream
    }

    printf("audio stream num: %d\n", audioStream);

    AVPacket *pkt = av_packet_alloc();
    av_init_packet(pkt);
    ret = av_read_frame(oc, pkt);
    if (ret < 0) {
        printf("av_read_frame failed\n");
        return -1;
    }

    if (pkt->stream_index == audioStream) {
        printf("read frame\n");
    }

    /* find the encoder */
    AVCodec *codec = avcodec_find_encoder(fmt->video_codec);
    if (!codec) {
        fprintf(stderr, "Could not find encoder for '%s'\n",
                avcodec_get_name(fmt->video_codec));
        exit(1);
    }

    if(avcodec_open(pInCodecCtx, pInCodec)<0)
    {
        printf("error avcodec_open failed.\n");
        return -1; // Could not open codec

    }

    static AVPacket packet;

    printf(" bit_rate = %d \r\n", pInCodecCtx->bit_rate);
    printf(" sample_rate = %d \r\n", pInCodecCtx->sample_rate);
    printf(" channels = %d \r\n", pInCodecCtx->channels);
    printf(" code_name = %s \r\n", pInCodecCtx->codec->name);
    printf(" block_align = %d\n",pInCodecCtx->block_align);

    uint8_t *pktdata;
    int pktsize;
    int out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE*100;
    uint8_t * inbuf = (uint8_t *)malloc(out_size);
    FILE* pcm;
    pcm = fopen("result.pcm","wb");
    long start = clock();
    while (av_read_frame(pInFmtCtx, &packet) >= 0)//pInFmtCtx中调用对应格式的packet获取函数
    {
        if(packet.stream_index==audioStream)//如果是音频
        {
            pktdata = packet.data;
            pktsize = packet.size;
            while(pktsize>0)
            {
                out_size = AVCODEC_MAX_AUDIO_FRAME_SIZE*100;
                //解码
                int len = avcodec_decode_audio2(pInCodecCtx, (short*)inbuf, &out_size, pktdata, pktsize);
                if (len < 0)
                {
                    printf("Error while decoding.\n");
                    break;
                }
                if(out_size > 0)
                {
                    fwrite(inbuf,1,out_size,pcm);//pcm记录
                    fflush(pcm);
                }
                pktsize -= len;
                pktdata += len;
            }
        }
        av_free_packet(&packet);
    }
    long end = clock();
    printf("cost time :%f\n",double(end-start)/(double)CLOCKS_PER_SEC);
    free(inbuf);
    fclose(pcm);
    if (pInCodecCtx!=NULL)
    {
        avcodec_close(pInCodecCtx);
    }
    av_close_input_file(pInFmtCtx);

    return 0;
}
