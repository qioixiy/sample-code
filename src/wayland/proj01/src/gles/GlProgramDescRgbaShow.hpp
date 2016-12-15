#ifndef _GlProgramDescRgbaShow_H_
#define _GlProgramDescRgbaShow_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GlProgramDesc.hpp"

class GlProgramDescRgbaShow: public GlProgramDesc {
public:
  virtual void Process(GlProgramObject *program);

  void BindTexture(GLint textureId);

private:
  GLuint texture;
};

#endif
