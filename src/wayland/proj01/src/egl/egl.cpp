
#include "utils/log/Log.hpp"
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
    LogE <<"Unable to open connection to local windowing system";
    return -1;
  }

  EGLint majorVersion;
  EGLint minorVersion;
  if(EGL_FALSE == eglInitialize(display, &majorVersion, &minorVersion))
  {
    LogE <<"Unable to initialize EGL-> Handle and recover";
    switch(eglGetError()) {
    case EGL_BAD_DISPLAY:
      LogE <<"display doesn't specify a valid EGLDisplay";
      break;
    case EGL_NOT_INITIALIZED:
      LogE <<"the EGL cannot be initialized";
      break;
    }
    return -2;
  }
  LogI <<"majorVersion="<<majorVersion<<", minorVersion="<<minorVersion;

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
    LogE <<"eglChooseConfig error";
    return -3;
  }
  LogI <<"numConfigs="<<numConfigs;

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
      LogE << "error: EGL_BAD_CONFIG";
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
      LogE <<"Check window and EGLConfig attributes to determine,"
        "compatibility, or verify that the EGLConfig,"
        "supports rendering to a window";
      break;
    case EGL_BAD_CONFIG:
      LogE <<"Verify that provided EGLConfig is valid";
      break;
    case EGL_BAD_NATIVE_WINDOW:
      LogE <<"Verify that provided EGLNativeWindow is valid";
      break;
    case EGL_BAD_ALLOC:
      LogE <<"Not enough resources available. Handle and recover";
      break;
    }
    return -5;
  }

  /* Making an EGLContext Current */
  int ret = eglMakeCurrent(display, surface, surface, context);
  if (ret != EGL_TRUE) {
    LogE <<"eglMakeCurrent error";
    return -6;
  }

  LogI <<"Version:"<<glGetString(GL_VERSION);
  LogI <<"Vendor:"<<glGetString(GL_VENDOR);
  LogI <<"Renderer:"<<glGetString(GL_RENDERER);
  LogI <<"Extensions:"<<glGetString(GL_EXTENSIONS);

#if 0
  glViewport(0, 0, 1024, 768);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  eglSwapBuffers(display, surface);
#endif

  return 0;
}
