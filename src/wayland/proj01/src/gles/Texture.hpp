
#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class Texture {
public:
  static GLuint Gen(unsigned char* , int, int, GLenum format);
};

#endif
