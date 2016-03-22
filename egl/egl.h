
#ifndef _EGL_H_
#define _EGL_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

struct egl_wayland {
    EGLDisplay display;
    EGLSurface surface;

    EGLContext context;
#define MAX_CONFIG 1
    EGLConfig config[MAX_CONFIG];
};

struct egl_wayland* egl_init(EGLNativeDisplayType, EGLNativeWindowType);

#endif
