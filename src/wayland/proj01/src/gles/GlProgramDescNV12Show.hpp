#ifndef _GlProgramDescNV12SHOW_H_
#define _GlProgramDescNV12SHOW_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GlProgramDesc.hpp"

class GlProgramDescNV12Show: public GlProgramDesc {
public:
  virtual void Process(GlProgramObject *program);

  void BindTextureY(GLint textureId);
  void BindTextureUV(GLint textureId);

private:
    GLuint textureY;
    GLuint textureUV;
};

#endif
