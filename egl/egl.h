
#ifndef _EGL_H_
#define _EGL_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct egl_env {
    EGLDisplay display;
    EGLSurface surface;

    EGLContext context;
#define MAX_CONFIG 1
    EGLConfig config[MAX_CONFIG];
};

struct egl_env* egl_init(EGLNativeDisplayType, EGLNativeWindowType);

#ifdef __cplusplus
}
#endif

#endif
