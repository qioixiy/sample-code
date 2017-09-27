#ifndef _YUV_RGB_H_
#define _YUV_RGB_H_

typedef unsigned char byte;

unsigned char *read_data_from_file (const char *path, long size);
byte *yuyv_2_rgb888 (byte * src, int width, int height);
#define yuyv_2_rgb yuy2_2_rgb
byte *yvyu_2_rgb (byte * src, int width, int height);
byte *vyuy_2_rgb (byte * src, int width, int height);
byte *yuy2_2_rgb (byte * src, int width, int height);
byte *uyvy_2_rgb (byte * src, int width, int height);
byte *yv16_2_rgb (byte * src, int width, int height);
byte *yv12_2_rgb (byte * src, int width, int height);
byte *nv21_2_rgb (byte * src, int width, int height);
byte *nv12_2_rgb (byte * src, int width, int height);
byte *nv16_2_rgb (byte * src, int width, int height);
byte *nv61_2_rgb (byte * src, int width, int height);

#endif
