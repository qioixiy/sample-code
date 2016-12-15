#ifndef _GlProgramDescDefault_H_
#define _GlProgramDescDefault_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GlProgramDesc.hpp"

class GlProgramDescDefault: public GlProgramDesc {
public:
  virtual void Process(GlProgramObject *program);
};

#endif
