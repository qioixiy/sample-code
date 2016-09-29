#ifndef _GLSL_PROG_OBJ_
#define _GLSL_PROG_OBJ_

#include <map>
#include <GLES2/gl2.h>
#include <string>
#include "Shader.hpp"

using namespace std;

class GLSLProgObj {
public:
  GLSLProgObj();
  int Run();

protected:
  virtual int Runner();

public:
  static map<string, Shader*> objs;

private:
  static int init();
};

#endif
