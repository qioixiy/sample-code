
#ifndef _EGL_HPP_
#define _EGL_HPP_

#include <wayland-egl.h>
#include <wayland-client.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class EGLEnv {
public:
  EGLEnv();
  EGLEnv(EGLNativeDisplayType, EGLNativeWindowType);

private:
  int init();

private:
  EGLNativeDisplayType mEGLNativeDisplayType;
  EGLNativeWindowType mEGLNativeWindowType;

public:
  EGLDisplay display;
  EGLSurface surface;

  EGLContext context;
#define MAX_CONFIG 1
  EGLConfig config[MAX_CONFIG];

};

#endif
