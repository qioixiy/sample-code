#include <stdlib.h>
#include <stddef.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>

int main(int argc, char **argv)
{
    const char* filepath = "error.wav";
    av_register_all();

    AVFormatContext *pFormatCtx;
    AVPacket *packet;

    pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx, filepath, NULL,NULL)!=0){
        printf("Couldn't open input stream.\n");
        return -1;
    }

    if(avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Couldn't find stream information.\n");
        return -1;
    }

    unsigned int audio_stream_index = -1;
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            break;
        }
    }

    AVCodecParameters* codecpar = pFormatCtx->streams[audio_stream_index]->codecpar;
    printf("channels=%d\n", codecpar->channels);
    printf("byte_per_coded_sample=%d\n", codecpar->bits_per_coded_sample/8);
    printf("byte_rate=%ld\n", codecpar->bit_rate/codecpar->bits_per_coded_sample/codecpar->channels);

    av_dump_format(pFormatCtx, 0, filepath, 0);

    packet = av_packet_alloc();
    av_init_packet(packet);

    while(av_read_frame(pFormatCtx, packet) >=0 ){
        printf("read frame\n");

        printf("stream_index=%d\n", packet->stream_index);
        printf("%p\n", packet->data);
        printf("%d\n", packet->size);
    }

    av_packet_unref(packet);

    return 0;
}
