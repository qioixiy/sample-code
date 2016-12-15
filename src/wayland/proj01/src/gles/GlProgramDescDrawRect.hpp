#ifndef _GlProgramDescDrawRect_H_
#define _GlProgramDescDrawRect_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GlProgramDesc.hpp"

class GlProgramDescDrawRect: public GlProgramDesc {
public:
  virtual void Process(GlProgramObject *program);
  void SetColor(int r, int g, int b);

private:
  int r, g, b;
};

#endif
