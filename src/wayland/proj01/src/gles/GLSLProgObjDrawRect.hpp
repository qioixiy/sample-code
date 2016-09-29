#ifndef _GLSL_PROG_OBJ_DRAWRECT_HPP_
#define _GLSL_PROG_OBJ_DRAWRECT_HPP_

#include <map>
#include <GLES2/gl2.h>
#include <string>
#include "Shader.hpp"
#include "GLSLProgObj.hpp"

using namespace std;

class GLSLProgObjDrawRect : public GLSLProgObj {
public:
  GLSLProgObjDrawRect(int r, int g, int b);
  void SetColor(int r, int g, int b);

protected:
  virtual int Runner();

public:
  int r, g, b;
};

#endif
