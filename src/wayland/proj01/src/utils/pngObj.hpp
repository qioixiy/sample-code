#ifndef _PNG_OBJ_HPP_
#define _PNG_OBJ_HPP_

#include <string>
#include <GLES2/gl2.h>

class pngObj {
public:
  enum COLOR_TYPE {
    COLOR_TYPE_RGB_ALPHA,
    COLOR_TYPE_RGB,
  };

public:
  pngObj(std::string path);
  virtual ~pngObj();

  int GetWidth();
  int GetHeight();
  unsigned char* GetData();
  COLOR_TYPE GetColorType();

private:
  int loadPngImageFile(std::string&);

public:
  COLOR_TYPE colorType;
  int width, height;
  unsigned char *data_buf;
};

#endif
