#include <stdio.h>
#include <stdlib.h>
#include "common/queue/queue.h"
#include "filebuffer.h"

#include "libavcodec/avcodec.h"
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
Queue_Header h264_queue_Header;
AVPacket *m_packet;

AVPacket *h264_packet_queue_get()
{
	AVPacket *data;
	if (Queue_get(&h264_queue_Header, &data) != 0) {
		return NULL;
	} else {
		return data;
	}
}

void h264_packet_queue_put(AVPacket *packet)
{
	unsigned char ret;
	
	ret = Queue_put(&h264_queue_Header, packet);
	if (ret != 0) {
		printf("h264_packet_queue_put error.\n");
	}
}

void h264_packet_queue_init(int size)
{
	static int init_flag = 0;
	int i = 0;
	
	// h264 queue malloc init
	if (init_flag == 0) {
		init_flag = 1;
		h264_queue_Header = Queue_Header_malloc(size+1);
	}
	
	//test with h264 stream file
	m_packet=(AVPacket *)malloc(sizeof(AVPacket) * size);
	memset(m_packet, 0, sizeof(AVPacket) * size);
	
	unsigned char *h264_stream_buffer = open_file_and_get_buffer("test.264");

	long h264_stream_buffer_size = *((long *)h264_stream_buffer);
	unsigned char *h264_stream_buffer_end = h264_stream_buffer + sizeof(void*) + h264_stream_buffer_size;
	unsigned long *nal_offset = malloc(sizeof (void*) * size);
	
	unsigned char *temp = h264_stream_buffer + sizeof(void*);
	printf("find\n");
	for (i = 0; i < size + 1; i++) {
		const static unsigned char nal_bytes[] = {0x00, 0x00, 0x00, 0x01};
		nal_offset[i] = find_bytestream_from_buffer(temp, h264_stream_buffer_end - temp, nal_bytes, sizeof(nal_bytes));
		printf("0x%x:0x%x, ", i, nal_offset[i]);
		temp = nal_offset[i]+4; //skip nal start flag 0x00000001
		printf("0x%02x%02x%02x%02x%02x%02x%02x%02x\n", temp[-4],temp[-3],temp[-2],temp[-1],temp[0],temp[1],temp[2],temp[3]);
	}
	printf("put\n");
	for (i = 0; i < size; i++) {
		AVPacket *pkt = &m_packet[i];

		av_init_packet(pkt);
		pkt->data = nal_offset[i];
		pkt->size = nal_offset[i+1] - nal_offset[i]+FF_MIN_BUFFER_SIZE;
		printf("0x%x, pkt:0x%x, pkt->data:0x%x, pkt->size:0x%x\n", i, pkt, pkt->data, pkt->size);
		
		h264_packet_queue_put(pkt);
	}
	printf("get\n");

#ifdef _TEST_
	for (i = 0; i < size; i++) {
	  AVPacket * packet;
	  if (!(packet = h264_packet_queue_get())) {
			printf("get warning\n");
	  } else {
	    printf("packet:0x%x\n", packet);
	    printf("packet->data:0x%x\n", packet->data);
	  }
	}
#endif
}

#ifdef _TEST_
int main() {
	h264_packet_queue_init(1000);
	printf("\n");
}
#endif
