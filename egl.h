
#ifndef _EGL_H_
#define _EGL_H_

struct egl_wayland {
    EGLDisplay display;
    EGLSurface surface;

    EGLContext context;
#define MAX_CONFIG 1
    EGLConfig config[MAX_CONFIG];
};

struct egl_wayland* egl_init(EGLNativeDisplayType, EGLNativeWindowType);

#endif
