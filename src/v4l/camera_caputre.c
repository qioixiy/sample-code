#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/videodev2.h>

int main() 
{
	int fd = 0;
	int ret = 0;

	//open device
	fd = open("/dev/video0", O_RDWR, 0);
	printf("open /dev/video0 ok, fd=%d\n", fd);
	
	v4l2_std_id std;
	do {
		ret = ioctl(fd, VIDIOC_QUERYSTD, &std);
	} while (ret == -1 && errno == EAGAIN);
	
	switch (std) {
	case V4L2_STD_NTSC:
		printf("NTSC\n");
		break;
	case V4L2_STD_PAL:
		printf("NTSC\n");
		break;
	default:
		printf("can not find, the result is %d\n", std);
		break;
	}

	//set farmat
	struct v4l2_format fmt;
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 720;
	fmt.fmt.pix.height = 576;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
		return -1;
	}

	//alloc memory
	struct v4l2_requestbuffers req;
	if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
		return -1;
	}
	printf("req.count=%d\n", req.count);

	typedef struct VideoBuffer {
		void* start;
		size_t length;
	}VideoBuffer;
	
	VideoBuffer* buffers = calloc(req.count, sizeof(*buffers));
	struct v4l2_buffer buf;
	
	int numBufs;
	for (numBufs = 0; numBufs < req.count; numBufs++) {
		memset(&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = numBufs;
		
		//get buffer
		if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) {
			return -1;
		}
		buffers[numBufs].length = buf.length;
		buffers[numBufs].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
					      MAP_SHARED, fd, buf.m.offset);
		if (buffers[numBufs].start == MAP_FAILED) {
			return -1;
		}

		//put queue
		if (ioctl(fd, VIDIOC_QBUF, &buf) == -1){
			return -1;
		}
	}
	
}
