#ifndef _GL_PPROGRAM_H_
#define _GL_PPROGRAM_H_

#include "utils/log/Log.hpp"

#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDesc.hpp"

class GlProgram {
public:
  GlProgram(string &vert, string &frag, GlProgramDesc *_desc) {
    mpGlProgramObject = new GlProgramObject(vert, frag);
    mpGlProgramDesc = _desc;
  }
  ~GlProgram() {
    delete mpGlProgramObject;
  }

  void Use() {
    mpGlProgramObject->Use();
  }
  void Process() {
    mpGlProgramDesc->Process(mpGlProgramObject);
  }

private:
  GlProgramObject *mpGlProgramObject;
  GlProgramDesc *mpGlProgramDesc;
};

#endif
