
#include <stdio.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "egl.h"

EGLDisplay _EGLDisplay;
EGLSurface _EGLSurface;

int egl_init(EGLNativeDisplayType *pEGLNativeDisplayType,
             EGLNativeWindowType _EGLNativeWindowType)
{
    _EGLDisplay = eglGetDisplay(*pEGLNativeDisplayType/* EGL_DEFAULT_DISPLAY */);
    if(_EGLDisplay == EGL_NO_DISPLAY)
    {
        printf("Unable to open connection to local windowing system\n");
        return -1;
    } else {
        printf("eglGetDisplay ok\n");
    }

    EGLint majorVersion;
    EGLint minorVersion;
    if(EGL_FALSE == eglInitialize(_EGLDisplay, &majorVersion, &minorVersion))
    {
        printf("Unable to initialize EGL. Handle and recover\n");
        switch(eglGetError()) {
        case EGL_BAD_DISPLAY:
            printf("display doesn’t specify a valid EGLDisplay\n");
            break;
        case EGL_NOT_INITIALIZED:
            printf("the EGL cannot be initialized\n");
            break;
        }
        return -2;
    } else {
        printf("eglInitialize ok\n");
        printf("majorVersion=%d, minorVersion=%d\n", majorVersion, minorVersion);
    }

//    eglBindAPI(EGL_OPENGL_ES_API);

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
    const EGLint MaxConfigs = 1;/* We'll only accept 10? configs */
    EGLConfig _EGLConfig[MaxConfigs];
    EGLint numConfigs;
    if(!eglChooseConfig(_EGLDisplay, eglChooseConfigAttribList, _EGLConfig, MaxConfigs,
                        &numConfigs)) {
        printf("eglChooseConfig error\n");
        return -3;
    } else {
        printf("eglChooseConfig ok\n");
        printf("numConfigs=%d\n", numConfigs);
    }

    /* Creating a Rendering Context */
    const EGLint ContextAttribList[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    EGLContext _EGLContext;
    _EGLContext = eglCreateContext(_EGLDisplay, _EGLConfig[0], EGL_NO_CONTEXT, ContextAttribList);
    if(_EGLContext == EGL_NO_CONTEXT)
    {
        if(eglGetError() == EGL_BAD_CONFIG)
        {
            printf("error and recover\n");
        }
    } else {
        printf("eglCreateContext ok\n");
    }

    /* Creating an On-Screen Rendering Area: The EGL Window */
    EGLint CreateWindowSurfaceAttribList[] = {
        EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
        EGL_NONE
    };
    _EGLSurface = eglCreateWindowSurface(_EGLDisplay, _EGLConfig[0], _EGLNativeWindowType, CreateWindowSurfaceAttribList);
    if(_EGLSurface == EGL_NO_SURFACE)
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
        return -1;
    } else {
        printf("eglCreateWindowSurface ok\n");
    }

    /* Making an EGLContext Current */
    int ret = eglMakeCurrent(_EGLDisplay, _EGLSurface, _EGLSurface, _EGLContext);
    if (ret != EGL_TRUE) {
        printf("eglMakeCurrent error\n");
        return -1;
    } else {
        printf("eglMakeCurrent ok\n");
    }

    printf("Version:%s\n", glGetString(GL_VERSION));
    printf("Vendor:%s\n", glGetString(GL_VENDOR));
    printf("Renderer:%s\n", glGetString(GL_RENDERER));
    printf("Extensions:%s\n", glGetString(GL_EXTENSIONS));

    /* glViewport(0, 0, 1024, 768); */
    /* glClearColor(1.0, 1.0, 1.0, 1.0); */
    /* glClear(GL_COLOR_BUFFER_BIT); */
    /* eglSwapBuffers(_EGLDisplay, _EGLSurface); */

    return 0;
}
