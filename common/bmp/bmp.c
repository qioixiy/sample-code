#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int GenBmpFile (U8 * pData, U8 bitCountPerPix, U32 width, U32 height,
                const char *filename);
U8 *GetBmpData (U8 * bitCountPerPix, U32 * width, U32 * height,
                const char *filename);
int
GenBmpFile (U8 * pData, U8 bitCountPerPix, U32 width, U32 height,
            const char *filename)
{
    FILE *fp = fopen (filename, "wb");
    if (!fp)
    {
        return 0;
    }

    U32 bmppitch = ((width * bitCountPerPix + 31) >> 5) << 2;
    U32 filesize = bmppitch * height;

    BITMAPFILE bmpfile;

    bmpfile.bfHeader.bfType = 0x4D42;
    bmpfile.bfHeader.bfSize =
        filesize + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
    bmpfile.bfHeader.bfReserved1 = 0;
    bmpfile.bfHeader.bfReserved2 = 0;
    bmpfile.bfHeader.bfOffBits =
        sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    bmpfile.biInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
    bmpfile.biInfo.bmiHeader.biWidth = width;
    bmpfile.biInfo.bmiHeader.biHeight = height;
    bmpfile.biInfo.bmiHeader.biPlanes = 1;
    bmpfile.biInfo.bmiHeader.biBitCount = bitCountPerPix;
    bmpfile.biInfo.bmiHeader.biCompression = 0;
    bmpfile.biInfo.bmiHeader.biSizeImage = 0;
    bmpfile.biInfo.bmiHeader.biXPelsPerMeter = 0;
    bmpfile.biInfo.bmiHeader.biYPelsPerMeter = 0;
    bmpfile.biInfo.bmiHeader.biClrUsed = 0;
    bmpfile.biInfo.bmiHeader.biClrImportant = 0;

    fwrite (&(bmpfile.bfHeader), sizeof (BITMAPFILEHEADER), 1, fp);
    fwrite (&(bmpfile.biInfo.bmiHeader), sizeof (BITMAPINFOHEADER), 1, fp);

    U8 *pEachLinBuf = (U8 *) malloc (bmppitch);
    memset (pEachLinBuf, 0, bmppitch);
    U8 BytePerPix = bitCountPerPix >> 3;
    U32 pitch = width * BytePerPix;
    if (pEachLinBuf)
    {
        int h, w;
        for (h = height - 1; h >= 0; h--)
        {
            for (w = 0; w < width; w++)
            {
                pEachLinBuf[w * BytePerPix + 0] = pData[h * pitch + w * BytePerPix + 0];
                pEachLinBuf[w * BytePerPix + 1] = pData[h * pitch + w * BytePerPix + 1];
                pEachLinBuf[w * BytePerPix + 2] = pData[h * pitch + w * BytePerPix + 2];
            }
            fwrite (pEachLinBuf, bmppitch, 1, fp);

        }
        free (pEachLinBuf);
    }

    fclose (fp);

    return 1;
}

U8*
GetBmpData (U8* bitCountPerPix, U32 * width, U32 * height,
            const char *filename)
{
    FILE *pf = fopen (filename, "rb");
    if (!pf)
    {
        return NULL;
    }

    BITMAPFILE bmpfile;
    fread (&(bmpfile.bfHeader), sizeof (BITMAPFILEHEADER), 1, pf);
    fread (&(bmpfile.biInfo.bmiHeader), sizeof (BITMAPINFOHEADER), 1, pf);

    if (bitCountPerPix)
    {
        *bitCountPerPix = bmpfile.biInfo.bmiHeader.biBitCount;
    }
    if (width)
    {
        *width = bmpfile.biInfo.bmiHeader.biWidth;
    }
    if (height)
    {
        *height = bmpfile.biInfo.bmiHeader.biHeight;
    }

    U32 bmppicth = (((*width) * (*bitCountPerPix) + 31) >> 5) << 2;
    U8 *pdata = (U8 *) malloc ((*height) * bmppicth);

    U8 *pEachLinBuf = (U8 *) malloc (bmppicth);
    memset (pEachLinBuf, 0, bmppicth);
    U8 BytePerPix = (*bitCountPerPix) >> 3;
    U32 pitch = (*width) * BytePerPix;

    /* bug? header was error use gimp gen bmp */
    fread (pEachLinBuf, 68, 1, pf);
    if (pdata && pEachLinBuf)
    {
        int w, h;
        for (h = (*height) - 1; h >= 0; h--)
        {
            fread (pEachLinBuf, bmppicth, 1, pf);
            for (w = 0; w < (*width); w++)
            {
                pdata[h * pitch + w * BytePerPix + 0] = pEachLinBuf[w * BytePerPix + 0];
                pdata[h * pitch + w * BytePerPix + 1] = pEachLinBuf[w * BytePerPix + 1];
                pdata[h * pitch + w * BytePerPix + 2] = pEachLinBuf[w * BytePerPix + 2];
            }
        }
        free (pEachLinBuf);
    }
    fclose (pf);

    return pdata;
}

typedef struct _RGB
{
    U8 b;
    U8 g;
    U8 r;
} RGB;
      
#ifdef _TEST
int
main (char argc, char *argv[])
{
    /* case 1 */
#define WIDTH   100
#define HEIGHT  100
    RGB pRGB[WIDTH][HEIGHT];
    memset (pRGB, 255, sizeof (pRGB));
    int i = 0, j = 0;
    int d = 1;
    for (i = d; i < WIDTH - d; i++)
    {
        for (j = d; j < HEIGHT - d; j++)
        {
            pRGB[i][j].b = 0xff;
            pRGB[i][j].g = 0x00;
            pRGB[i][j].r = 0x00;
        }
    }
    GenBmpFile ((U8 *) pRGB, 24, WIDTH, HEIGHT, "out.bmp");

    /* case 2 */
    U8 bitCountPerPix;
    U32 width, height;
    U8 *pdata = GetBmpData (&bitCountPerPix, &width, &height, "in.bmp");

    if (pdata)
    {
        GenBmpFile (pdata, bitCountPerPix, width, height, "out1.bmp");
        free (pdata);
    }

    return 0;
}
#endif
