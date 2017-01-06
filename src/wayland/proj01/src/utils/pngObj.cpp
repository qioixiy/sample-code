#include <png.h>
#include "pngObj.hpp"

pngObj::pngObj(std::string filePath)
  : width(0)
  , height(0)
  , data_buf(NULL)
{
  loadPngImageFile(filePath);
}

pngObj::~pngObj()
{
  if (data_buf) delete[] data_buf;
}

int
pngObj::GetWidth()
{
  return width;
}

int
pngObj::GetHeight()
{
  return height;
}

unsigned char*
pngObj::GetData()
{
  return data_buf;
}

pngObj::COLOR_TYPE
pngObj::GetColorType()
{
  return colorType;
}

int
pngObj::loadPngImageFile(std::string& filePath)
{
#define PNG_BYTES_TO_CHECK 4

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep* row_pointers;
  char buf[PNG_BYTES_TO_CHECK];
  int w, h, x, y, temp, color_type;

  fp = fopen(filePath.c_str(), "rb");
  if(fp == NULL) {
    return -1;
  }

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  info_ptr = png_create_info_struct(png_ptr);

  setjmp(png_jmpbuf(png_ptr));
  temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
  if(temp < PNG_BYTES_TO_CHECK) {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    return -3;
  }
  temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
  if(temp != 0) {             // is not a png file type
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    return -4;
  }

  // reset file pointer
  rewind(fp);
  // start to read file
  png_init_io(png_ptr, fp);
  // read png picture info
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
  // get picture color type
  color_type = png_get_color_type(png_ptr, info_ptr);
  // get width and height
  w = png_get_image_width(png_ptr, info_ptr);
  h = png_get_image_height(png_ptr, info_ptr);
  // read rgba
  row_pointers = png_get_rows(png_ptr, info_ptr);
  unsigned char *data;
  int index = 0;

  switch(color_type) {
  case PNG_COLOR_TYPE_RGB_ALPHA:
    colorType = COLOR_TYPE_RGB_ALPHA;
    data = new unsigned char[w*h*4];
    data_buf = data;
    width = w;
    height = h;
    for(y=0; y<h; ++y) {
      for(x=0; x<w*4;) {
        data[index++] = row_pointers[y][x++]; // red
        data[index++] = row_pointers[y][x++]; // green
        data[index++] = row_pointers[y][x++]; // blue
        data[index++] = row_pointers[y][x++]; // alpha
      }
    }
    break;
  case PNG_COLOR_TYPE_RGB:
    colorType = COLOR_TYPE_RGB;
    data = new unsigned char[w*h*3];
    data_buf = data;
    width = w;
    height = h;
    for(y=0; y<h; ++y) {
      for(x=0; x<w*3;) {
        data[index++] = row_pointers[y][x++]; // red
        data[index++] = row_pointers[y][x++]; // green
        data[index++] = row_pointers[y][x++]; // blue
      }
    }
    break;
  default:
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    return -2;
  }
  png_destroy_read_struct(&png_ptr, &info_ptr, 0);
  return 0;
}
