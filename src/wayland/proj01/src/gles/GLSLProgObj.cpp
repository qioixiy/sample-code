#include "GLSLProgObj.hpp"

#include "utils/log/log.h"
#include "utils/log/Log.hpp"
#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

map<string, Shader*> GLSLProgObj::objs;

static string sGLSLBasePath = "res/glsl_shaders/";
static string sGLSLShaders[][3] =
{
  {"default", "default.vert", "default.frag"},
  {"rgba", "rgbashow.vert", "rgbashow.frag"},
  {"drawrect", "drawrect.vert", "drawrect.frag"},
};

GLSLProgObj::GLSLProgObj()
{
  init();
}

int GLSLProgObj::init()
{
  static int flag = 0;
  if (flag != 0) {
    return -1;
  }

  flag = 1;

  for (int i = 0; i < sizeof(sGLSLShaders)/sizeof(sGLSLShaders[0]); i++) {
    objs[sGLSLShaders[i][0]] = new Shader(
      (sGLSLBasePath + sGLSLShaders[i][1]).c_str(),
      (sGLSLBasePath + sGLSLShaders[i][2]).c_str());
  }

  return 0;
}

int GLSLProgObj::Run()
{
  return Runner();
}

int GLSLProgObj::Runner()
{
  return 0;
}
