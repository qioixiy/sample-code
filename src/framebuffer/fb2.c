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

	long screensize = 0;
	unsigned char *fbp = 0;
	int x = 0;
	int y = 0;
	long location = 0;
		
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
	
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	fbp = (unsigned char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);
#if 0
	x = 100;
	y = 100;
	location = x * (vinfo.bits_per_pixel / 8) + y  *  finfo.line_length;
	
	*(fbp + location) = 100;
	*(fbp + location + 1) = 15;
	*(fbp + location + 2) = 200;
	*(fbp + location + 3) = 0;
#endif
	int i = 0;
	while(i < 100 * 100 * 100) {
		fbp[i] = i;
		i++;
	}
	
	munmap (fbp, screensize);
	close (fp);

	return 0;
}
