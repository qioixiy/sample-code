
#include <stdlib.h>
#include <png.h>

#include "png_load.h"

#define PNG_BYTES_TO_CHECK 4

int load_png_image(const char *filepath,
                   struct pngload_attribute *png_attr)
{
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep* row_pointers;
    char buf[PNG_BYTES_TO_CHECK];
    int w, h, x, y, temp, color_type;

    fp = fopen( filepath, "rb" );
    if( fp == NULL ) { 
        return -1;
    }

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
    info_ptr = png_create_info_struct( png_ptr );

    setjmp( png_jmpbuf(png_ptr) ); 
    /* 读取PNG_BYTES_TO_CHECK个字节的数据 */
    temp = fread( buf, 1, PNG_BYTES_TO_CHECK, fp );
    /* 若读到的数据并没有PNG_BYTES_TO_CHECK个字节 */
    if( temp < PNG_BYTES_TO_CHECK ) {
        fclose(fp);
        png_destroy_read_struct( &png_ptr, &info_ptr, 0);
        return -3;
    }
    /* 检测数据是否为PNG的签名 */
    temp = png_sig_cmp( (png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK );
    /* 如果不是PNG的签名，则说明该文件不是PNG文件 */
    if( temp != 0 ) {
        fclose(fp);
        png_destroy_read_struct( &png_ptr, &info_ptr, 0);
        return -4;
    }
        
    /* 复位文件指针 */
    rewind( fp );
    /* 开始读文件 */
    png_init_io( png_ptr, fp ); 
    /* 读取PNG图片信息 */
    png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0 );
    /* 获取图像的色彩类型 */
    color_type = png_get_color_type( png_ptr, info_ptr );
    /* 获取图像的宽高 */
    png_attr->width = w = png_get_image_width( png_ptr, info_ptr );
    png_attr->height = h = png_get_image_height( png_ptr, info_ptr );
    printf("w=%d,h=%d\n", w, h);
    /* 获取图像的所有行像素数据，row_pointers里边就是rgba数据 */
    row_pointers = png_get_rows( png_ptr, info_ptr );
    unsigned char *data;
    int index = 0;

    /* 根据不同的色彩类型进行相应处理 */
    png_attr->color_type = color_type;
    switch( color_type ) {
    case PNG_COLOR_TYPE_RGB_ALPHA:
        printf("rgba\n");
        data = malloc(w*h*4);
        png_attr->buf = data;
        for( y=0; y<h; ++y ) {
            for( x=0; x<w*4; ) {
                /* 以下是RGBA数据，需要自己补充代码，保存RGBA数据 */
                data[index++] = row_pointers[y][x++]; // red
                data[index++] = row_pointers[y][x++]; // green
                data[index++] = row_pointers[y][x++]; // blue
                data[index++] = row_pointers[y][x++]; // alpha
            }
        }
        break;

    case PNG_COLOR_TYPE_RGB:
        printf("rgb\n");
        data = malloc(w*h*3);
        png_attr->buf = data;
        for( y=0; y<h; ++y ) {
            for( x=0; x<w*3; ) {
                data[index++] = row_pointers[y][x++]; // red
                data[index++] = row_pointers[y][x++]; // green
                data[index++] = row_pointers[y][x++]; // blue
            }
        }
        break;
        /* 其它色彩类型的图像就不读了 */
    default:
        fclose(fp);
        png_destroy_read_struct( &png_ptr, &info_ptr, 0);
        return -2;
    }
    png_destroy_read_struct( &png_ptr, &info_ptr, 0);
    return 0;
}

GLuint png_color_type_GL(int color_type)
{
    GLuint ret;
    switch(color_type) {
    case PNG_COLOR_TYPE_RGB_ALPHA:
        ret = GL_RGBA;
        break;
    case PNG_COLOR_TYPE_RGB:
        ret = GL_RGB;
        break;
    default:
        printf("unkown png color\n");
    }
    return ret;
}

#if defined DEBUG
#define t_main main
#endif
int t_main()
{
    struct pngload_attribute png_attr;
    load_png_image("png-test.png", &png_attr);
}
