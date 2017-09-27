#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

int main() {
	int fp = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;

	fp = open("/dev/fb0", O_RDWR);
	if (fp < 0) {
		printf("error\n");
		exit(1);
	}

	if (ioctl(fp, FBIOGET_FSCREENINFO, &finfo)) {
		printf("error reading fixed information\n");
		exit(2);
	}

	if (ioctl(fp, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("error reading variable information\n");
		exit(3);
	}
	
	printf("the mem is :%d\n", finfo.smem_len);
	printf("the line_length is :%d\n", finfo.line_length);
	printf("the xres is :%d\n", vinfo.xres);
	printf("the yres is :%d\n", vinfo.yres);
	printf("the bits_per_pixel is :%d\n", vinfo.bits_per_pixel);
	
	return 0;
}
