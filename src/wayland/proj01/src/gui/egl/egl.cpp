
#include <stdio.h>
#include <stdlib.h>

#include "egl.hpp"

EGLEnv::EGLEnv()
{
    ;
}

EGLEnv::EGLEnv(EGLNativeDisplayType _EGLNativeDisplayType,
               EGLNativeWindowType _EGLNativeWindowType)
{
    mEGLNativeDisplayType = _EGLNativeDisplayType;
    mEGLNativeWindowType = _EGLNativeWindowType;
    init();
}

int EGLEnv::init()
{
    display = eglGetDisplay(mEGLNativeDisplayType/* EGL_DEFAULT_DISPLAY */);
    if(display == EGL_NO_DISPLAY)
    {
        printf("Unable to open connection to local windowing system\n");
        return -1;
    }

    EGLint majorVersion;
    EGLint minorVersion;
    if(EGL_FALSE == eglInitialize(display, &majorVersion, &minorVersion))
    {
        printf("Unable to initialize EGL-> Handle and recover\n");
        switch(eglGetError()) {
        case EGL_BAD_DISPLAY:
            printf("display doesn't specify a valid EGLDisplay\n");
            break;
        case EGL_NOT_INITIALIZED:
            printf("the EGL cannot be initialized\n");
            break;
        }
        return -2;
    }
    printf("majorVersion=%d, minorVersion=%d\n",
           majorVersion, minorVersion);

    eglBindAPI(EGL_OPENGL_ES_API);

/* Letting EGL Choose the Config */
    EGLint eglChooseConfigAttribList[] = {
#if 1
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_DEPTH_SIZE, 1,
        EGL_NONE
#else
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_ALPHA_SIZE, 0,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_DEPTH_SIZE, 8,
        EGL_SAMPLE_BUFFERS, 1,
        EGL_SAMPLES, 4,  // This is for 4x MSAA.
        EGL_NONE
#endif
    };

    EGLint numConfigs;
    if(!eglChooseConfig(display,
                        eglChooseConfigAttribList,
                        config, MAX_CONFIG,
                        &numConfigs)) {
        printf("eglChooseConfig error\n");
        return -3;
    }
    printf("numConfigs=%d\n", numConfigs);

    /* Creating a Rendering Context */
    const EGLint ContextAttribList[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    context = eglCreateContext(display,
                               config[0],
                               EGL_NO_CONTEXT,
                               ContextAttribList);
    if(context == EGL_NO_CONTEXT)
    {
        if(eglGetError() == EGL_BAD_CONFIG)
        {
            printf("error: EGL_BAD_CONFIG\n");
        }
        return -4;
    }

    /* Creating an On-Screen Rendering Area: The EGL Window */
    EGLint CreateWindowSurfaceAttribList[] = {
        EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
        EGL_NONE
    };
    surface = eglCreateWindowSurface(display,
                                     config[0],
                                     mEGLNativeWindowType,
                                     CreateWindowSurfaceAttribList);
    if(surface == EGL_NO_SURFACE)
    {
        switch(eglGetError())
        {
        case EGL_BAD_MATCH:
            printf("Check window and EGLConfig attributes to determine\n"
                   "compatibility, or verify that the EGLConfig\n"
                   "supports rendering to a window\n");
            break;
        case EGL_BAD_CONFIG:
            printf("Verify that provided EGLConfig is valid\n");
            break;
        case EGL_BAD_NATIVE_WINDOW:
            printf("Verify that provided EGLNativeWindow is valid\n");
            break;
        case EGL_BAD_ALLOC:
            printf("Not enough resources available. Handle and recover\n");
            break;
        }
        return -5;
    }

    /* Making an EGLContext Current */
    int ret = eglMakeCurrent(display, surface, surface, context);
    if (ret != EGL_TRUE) {
        printf("eglMakeCurrent error\n");
        return -6;
    }

    printf("Version:%s\n", glGetString(GL_VERSION));
    printf("Vendor:%s\n", glGetString(GL_VENDOR));
    printf("Renderer:%s\n", glGetString(GL_RENDERER));
    printf("Extensions:%s\n", glGetString(GL_EXTENSIONS));

#if 0
    glViewport(0, 0, 1024, 768);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(egl->display, egl->surface);
#endif

    return 0;
}
