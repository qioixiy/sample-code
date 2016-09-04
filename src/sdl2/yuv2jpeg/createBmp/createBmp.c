#include "createBmp.h"

BOOL CreateBmp(const char *filename, uint8_t *pRGBBuffer, int width, int height, int bpp)
{  
 BITMAPFILEHEADER bmpheader;  
 BITMAPINFOHEADER bmpinfo;  
 FILE *fp = NULL;  
  
 fp = fopen(filename,"wb");  
 if( fp == NULL )  
 {  
  return FALSE;  
 }  
  
 bmpheader.bfType = ('M' <<8)|'B';  
 bmpheader.bfReserved1 = 0;  
 bmpheader.bfReserved2 = 0;  
 bmpheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  
 bmpheader.bfSize = bmpheader.bfOffBits + width*height*bpp/8;  
  
 bmpinfo.biSize = sizeof(BITMAPINFOHEADER);  
 bmpinfo.biWidth = width;  
 bmpinfo.biHeight = 0 - height;  
 bmpinfo.biPlanes = 1;  
 bmpinfo.biBitCount = bpp;  
 bmpinfo.biCompression = BI_RGB;  
 bmpinfo.biSizeImage = 0;  
 bmpinfo.biXPelsPerMeter = 100;  
 bmpinfo.biYPelsPerMeter = 100;  
 bmpinfo.biClrUsed = 0;  
 bmpinfo.biClrImportant = 0;  
  
 fwrite(&bmpheader,sizeof(BITMAPFILEHEADER),1,fp);  
 fwrite(&bmpinfo,sizeof(BITMAPINFOHEADER),1,fp);  
 fwrite(pRGBBuffer, width * height * (bpp/8),1,fp);
 fclose(fp);  
 fp = NULL;  
  
 return TRUE;  
}

/* gcc createBmp.c  -o createBmp -D_TEST */
#if _TEST
int main(int argc, char **argv)
{
	int width = 500;
	int height = 500;
	int bpp = 32;
	int size = width * height * (bpp/8);
	
	unsigned char *pbuf = (unsigned char *)malloc(size);
	memset(pbuf, 0, size);
	
	CreateBmp("CreateBmp_test.bmp", pbuf, width, height, bpp);
}
#endif
