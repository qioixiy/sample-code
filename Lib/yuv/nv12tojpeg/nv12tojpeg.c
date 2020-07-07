#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
 
// Conversion from YUV to RGB24
static long int crv_tab[256];
static long int cbu_tab[256];
static long int cgu_tab[256];
static long int cgv_tab[256];
static long int tab_76309[256];
static unsigned char clp[1024];//for clip in CCIR601

//Initialize conversion table for YUV420 to RGB
void InitConvertTable()
{
 
	long int crv,cbu,cgu,cgv;
	int i,ind;  
      
	crv = 104597; cbu = 132201;
	cgu = 25675;  cgv = 53279;
   
	for (i = 0; i < 256; i++) {
 
		crv_tab[i] = (i-128) * crv;
		cbu_tab[i] = (i-128) * cbu;
		cgu_tab[i] = (i-128) * cgu;
		cgv_tab[i] = (i-128) * cgv;
		tab_76309[i] = 76309*(i-16);
    
	}
  
	for (i=0; i<384; i++)
		clp[i] =0;
	ind=384;
	for (i=0;i<256; i++)
		clp[ind++]=i;
	ind=640;
	for (i=0;i<384;i++)
		clp[ind++]=255;
 
}
 
//  Convert from YUV to RGB24
void ConvertYUV2RGB(unsigned char *src,unsigned char *dst,
					int width,int height)
{
	unsigned char *puv = src + width*height;
 
	int y1,y2,u,v;
	unsigned char *py1,*py2;
	int i,j, c1, c2, c3, c4;
	unsigned char *d1, *d2;

	{
		static int flag = 0;
		if (flag == 0) {
			flag = 1;
			InitConvertTable();
		}
	}
	
	py1=src;
	py2=py1+width;
	d1=dst;
	d2=d1+3*width;
	for (j = 0; j < height; j += 2) {
 		for (i = 0; i < width; i += 2) {
 			u = *puv++;
			v = *puv++;
			
			c1 = crv_tab[v];
			c2 = cgu_tab[u];
			c3 = cgv_tab[v];
			c4 = cbu_tab[u];
//up-left
            y1 = tab_76309[*py1++];
			*d1++ = clp[384+((y1 + c1)>>16)]; 
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
            *d1++ = clp[384+((y1 + c4)>>16)];
//down-left
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)]; 
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
            *d2++ = clp[384+((y2 + c4)>>16)];
//up-right
			y1 = tab_76309[*py1++];
			*d1++ = clp[384+((y1 + c1)>>16)]; 
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
			*d1++ = clp[384+((y1 + c4)>>16)];
//down-right
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)]; 
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
            *d2++ = clp[384+((y2 + c4)>>16)];
		}
		d1 += 3*width;
		d2 += 3*width;
		py1+=   width;
		py2+=   width; 
	}      
}

static void jpegWrite(unsigned char* img, int width, int height, char *filename)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];

    FILE *outfile = fopen(filename, "wb" );

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

static void Process(unsigned char* p, int width, int height, char * outfilename)
{
	unsigned char *rgb_buf = malloc(width * height * 3);
	
	ConvertYUV2RGB(p, rgb_buf, width, height);
	
    jpegWrite(rgb_buf, width, height, outfilename);

	free(rgb_buf);
}

int main(int argc, char **argv) {

	int width = 720;
	int height = 480;

    int frame = width * height * 3 / 2;
    unsigned char *src = malloc(frame);
    
    char *filename;
	
	filename = "res/VideoCH0.720x480.nv12";
	
    FILE *fp = fopen(filename, "rb");
    fread(src, frame, 1, fp);
	fclose(fp);
	
	Process(src, width, height, "out.jpg");


	free(src);
}
