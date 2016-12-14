#ifndef _GL_PPROGRAM_H_
#define _GL_PPROGRAM_H_

#include <string>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace std;

class GlProgram {
public:
  GlProgram();
  void Use();
  int MakeProgramFromFile(string &vert, string &frag);
  int MakeProgramFromString(string &vert, string &frag);

private:
  GLint compile(GLenum type, const char *shaderStr);

private:
  GLint glProgramObject;
};

#endif
