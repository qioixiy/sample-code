#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
#include "createBmp/createBmp.h"

static void jpegWrite(unsigned char* img, int width, int height)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];

    FILE *outfile = fopen("out.jpeg", "wb" );

// create jpeg data
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);
// set image parameters
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

// set jpeg compression parameters to default
    jpeg_set_defaults(&cinfo);
// and then adjust quality setting
    jpeg_set_quality(&cinfo, 100, TRUE);
// start compress
    jpeg_start_compress(&cinfo, TRUE);
// feed data
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &img[cinfo.next_scanline * cinfo.image_width *
                              cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
// finish compression
    jpeg_finish_compress(&cinfo);
// destroy jpeg data
    jpeg_destroy_compress(&cinfo);
// close output file
    fclose(outfile);
}

typedef struct RGB {
    unsigned char r, g, b;
}RGB;

int R = 0;
int G = 1;
int B = 2;

static RGB yuvTorgb(unsigned char Y, unsigned char U, unsigned char V){
    RGB rgb;
    int r, g, b;

    r = (int)((Y&0xff) + 1.4075 * ((V&0xff)-128));
    g = (int)((Y&0xff) - 0.3455 * ((U&0xff)-128) - 0.7169*((V&0xff)-128));
    b = (int)((Y&0xff) + 1.779 * ((U&0xff)-128));

    rgb.r = (r<0? 0: r>255? 255 : r);
    rgb.g = (g<0? 0: g>255? 255 : g);
    rgb.b = (b<0? 0: b>255? 255 : b);
    return rgb;
}

static unsigned char* NV12ToRGB(unsigned char *src, int width, int height) {
    int numOfPixel = width * height;
    int positionOfU = numOfPixel;

    unsigned char* rgb = malloc(numOfPixel * 3);
    
    int i = 0, j = 0;

    for(i = 0; i < height; i++){
        int startY = i*width;
        int step = i/2*width;
        int startU = positionOfU + step;
        for(j = 0; j < width; j++){
            int Y = startY + j;
            int U = startU + j/2;
            int V = U + 1;
            int indexrgb = Y*3;
            RGB tmp = yuvTorgb(src[Y], src[U], src[V]);

            rgb[indexrgb+R] = tmp.r;
            rgb[indexrgb+G] = tmp.g;
            rgb[indexrgb+B] = tmp.b;

        }
    }

    return rgb;
}  

void yuv_to_rgb(  unsigned char * src[3],  // yuv420
				  int stride_s,     // stride of lum, assume strides of U,V are stride_s/2
				  int W,       // width, assume W%2 == 0
				  int H,       // height, assume H%2 == 0
				  unsigned char* _dst);    // rgb32

static void imageProcess(const void* p, int width, int height)
{
    unsigned char* src = (unsigned char*)p;

#if 0
    unsigned char *dst = NV12ToRGB(src, width, height);
	unsigned char *rgb_buf = malloc(width * height * 3);

	NV12ToRGB(src, width, height);
	
    jpegWrite(dst, width, height);
#else
	unsigned char *yuv_src[3];
	yuv_src[0] = src;
	yuv_src[2] = src+width*height;
	yuv_src[1] = src+width*height + width*height/4;
	unsigned char *rgb_buf = malloc(width * height * 3);

	yuv_to_rgb(yuv_src, 0, width, height, rgb_buf);
	
    jpegWrite(rgb_buf, width, height);
    BOOL CreateBmp(const char *filename, uint8_t *pRGBBuffer, int width, int height, int bpp);
    CreateBmp("out.bmp", rgb_buf, width, height, 24);

#endif
}

int main(int argc, char **argv) {
    int i = 0;
#if 0
    int width = 240;
    int height = 320;
#else 
	int width = 1366;
	int height = 768;
#endif

    int frame = width * height * 3 / 2;
    unsigned char *src = malloc(frame);
    
    //memset(src, 0, frame);

#if 0
    char *filename = "butterfly.nv12.240x320.yuv";
#else
    char *filename = "butterfly.yuv420p.240x320.yuv";
#endif
	filename = "scr.yuv420p.1366x768.yuv";
    FILE *fp = fopen(filename, "rb");
    fread(src, frame, 1, fp);

    imageProcess(src, width, height);

}
