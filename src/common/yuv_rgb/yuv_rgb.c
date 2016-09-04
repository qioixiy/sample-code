/*
 * url: http://blog.csdn.net/huiguixian/article/details/17334195
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "yuv_rgb.h"

#define R 0
#define G 1
#define B 2
typedef struct
{
    int r, g, b;
} struct_rgb;

static int
scope (int s, int l, int g)
{
    if (s > g)
    {
        return g;
    }
    else if (s < l)
    {
        return l;
    }
    else
    {
        return s;
    }
}

static void
yuv_2_rgb (int y, int u, int v, int *r, int *g, int *b)
{
    int _r, _g, _b;

#if 1
    _r = (y & 0xff) + 1.4075 * ((v & 0xff) - 128);
    _g = (y & 0xff) - 0.3455 * ((u & 0xff) - 128) - 0.7169 * ((v & 0xff) - 128);
    _b = (y & 0xff) + 1.779 * ((u & 0xff) - 128);
#else
    _r = y + 1.042 * (v - 128);
    _g = y - 0.34414 * (u - 128) - 0.71414 * (v - 128);
    _b = y + 1.772 * (u - 128);
#endif
    _r = scope (_r, 0, 255);
    _g = scope (_g, 0, 255);
    _b = scope (_b, 0, 255);

    *r = _r;
    *g = _g;
    *b = _b;
}

unsigned char *
read_data_from_file (const char *path, long size)
{
    FILE *fp;

    if ((fp = fopen (path, "rb")) == NULL)
    {
        printf ("cant open the file");
        exit (0);
    }

    unsigned char *buffer = malloc (size);
    fread (buffer, size, 1, fp);
    fclose (fp);

    return buffer;
}

byte *
yuyv_2_rgb888 (byte * src, int width, int height)
{
    unsigned char y1, y2, u, v;
    int r1, g1, b1, r2, g2, b2;
    int numOfPixel = width * height;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width / 2; j++)
        {
            y1 = src[(i * width / 2 + j) * 4];
            u = src[(i * width / 2 + j) * 4 + 1];
            y2 = src[(i * width / 2 + j) * 4 + 2];
            v = src[(i * width / 2 + j) * 4 + 3];

            yuv_2_rgb (y1, u, v, &r1, &g1, &b1);
            yuv_2_rgb (y2, u, v, &r2, &g2, &b2);

            *(rgb + ((height - 1 - i) * width / 2 + j) * 6) =
                (unsigned char) r1;
            *(rgb + ((height - 1 - i) * width / 2 + j) * 6 + 1) =
                (unsigned char) g1;
            *(rgb + ((height - 1 - i) * width / 2 + j) * 6 + 2) =
                (unsigned char) b1;
            *(rgb + ((height - 1 - i) * width / 2 + j) * 6 + 3) =
                (unsigned char) r2;
            *(rgb + ((height - 1 - i) * width / 2 + j) * 6 + 4) =
                (unsigned char) g2;
            *(rgb + ((height - 1 - i) * width / 2 + j) * 6 + 5) =
                (unsigned char) b2;
        }
    }
    return rgb;
}

//YVYU是YUV422格式，排列是(YVYU)，是1 plane  
byte *
yvyu_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int lineWidth = 2 * width;
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * lineWidth;
        for (j = 0; j < lineWidth; j += 4)
        {
            int Y1 = j + startY;
            int Y2 = Y1 + 2;
            int V = Y1 + 1;
            int U = Y1 + 3;
            int index = (Y1 >> 1) * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y1], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
            index += 3;
            yuv_2_rgb (src[Y2], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//VYUY是YUV422格式，排列是(VYUY)，是1 plane  
byte *
vyuy_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int lineWidth = 2 * width;
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startV = i * lineWidth;
        for (j = 0; j < lineWidth; j += 4)
        {
            int V = j + startV;
            int Y1 = V + 1;
            int Y2 = V + 3;
            int U = V + 2;
            int index = (U >> 1) * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y1], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
            index += 3;
            yuv_2_rgb (src[Y2], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//YUY2是YUV422格式，排列是(YUYV)，是1 plane  
byte *
yuy2_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int lineWidth = 2 * width;
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * lineWidth;
        for (j = 0; j < lineWidth; j += 4)
        {
            int Y1 = j + startY;
            int Y2 = Y1 + 2;
            int U = Y1 + 1;
            int V = Y1 + 3;
            int index = (Y1 >> 1) * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y1], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
            index += 3;
            yuv_2_rgb (src[Y2], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//UYVY是YUV422格式，排列是(UYVY)，是1 plane  
byte *
uyvy_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int lineWidth = 2 * width;
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startU = i * lineWidth;
        for (j = 0; j < lineWidth; j += 4)
        {
            int U = j + startU;
            int Y1 = U + 1;
            int Y2 = U + 3;
            int V = U + 2;
            int index = (U >> 1) * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y1], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
            index += 3;
            yuv_2_rgb (src[Y2], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//YV16是yuv422格式，是三个plane，(Y)(U)(V)  
byte *
yv16_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfU = numOfPixel;
    int positionOfV = numOfPixel / 2 + numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = i * width / 2;
        int startU = positionOfU + step;
        int startV = positionOfV + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int U = startU + j / 2;
            int V = startV + j / 2;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//YV12是yuv420格式，是3个plane，排列方式为(Y)(V)(U)  
byte *
yv12_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfV = numOfPixel;
    int positionOfU = numOfPixel / 4 + numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = (i / 2) * (width / 2);
        int startV = positionOfV + step;
        int startU = positionOfU + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int V = startV + j / 2;
            int U = startU + j / 2;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//NV21是YUV420格式，排列是(Y), (VU)，是2 plane  
byte *
nv21_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfV = numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = i / 2 * width;
        int startV = positionOfV + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int V = startV + j / 2;
            int U = V + 1;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//NV12是YUV420格式，排列是(Y), (UV)，是2 plane  
byte *
nv12_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfU = numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = i / 2 * width;
        int startU = positionOfU + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int U = startU + j / 2;
            int V = U + 1;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//NV16是YUV422格式，排列是(Y), (UV)，是2 plane  
byte *
nv16_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfU = numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = i * width;
        int startU = positionOfU + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int U = startU + j / 2;
            int V = U + 1;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}

//NV61是YUV422格式，排列是(Y), (VU)，是2 plane  
byte *
nv61_2_rgb (byte * src, int width, int height)
{
    int numOfPixel = width * height;
    int positionOfV = numOfPixel;
    byte *rgb = malloc (sizeof (byte) * numOfPixel * 3);
    int i, j;
    for (i = 0; i < height; i++)
    {
        int startY = i * width;
        int step = i * width;
        int startV = positionOfV + step;
        for (j = 0; j < width; j++)
        {
            int Y = startY + j;
            int V = startV + j / 2;
            int U = V + 1;
            int index = Y * 3;
            struct_rgb tmp;
            yuv_2_rgb (src[Y], src[U], src[V], &tmp.r, &tmp.g, &tmp.b);
            rgb[index + R] = tmp.r;
            rgb[index + G] = tmp.g;
            rgb[index + B] = tmp.b;
        }
    }
    return rgb;
}
