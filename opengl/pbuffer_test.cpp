#include <string.h>
#include <iostream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <cairo/cairo.h>

int main(int argc, char *argv[])
{
  EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2,
				  EGL_NONE };
  // Step 1 - Get the default display.
  EGLDisplay eglDisplay = eglGetDisplay((EGLNativeDisplayType)0);
  // Step 2 - Initialize EGL.
  eglInitialize(eglDisplay, 0, 0);
  // Step 3 - Make OpenGL ES the current API.
  eglBindAPI(EGL_OPENGL_ES_API);
  // Step 4 - Specify the required configuration attributes.
  EGLint pi32ConfigAttribs[5];
  pi32ConfigAttribs[0] = EGL_SURFACE_TYPE;
  pi32ConfigAttribs[1] = EGL_WINDOW_BIT;
  pi32ConfigAttribs[2] = EGL_RENDERABLE_TYPE;
  pi32ConfigAttribs[3] = EGL_OPENGL_ES2_BIT;
  pi32ConfigAttribs[4] = EGL_NONE;
  // Step 5 - Find a config that matches all requirements.
  int iConfigs;
  EGLConfig eglConfig;
  eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs);
  if (iConfigs != 1)
    {
      printf("Error: eglChooseConfig(): config not found.\n");
      exit(-1);
    }
  // Step 6 - Create a surface to draw to.
  EGLSurface eglSurface;
  eglSurface = eglCreatePbufferSurface(eglDisplay, eglConfig, NULL);
  // Step 7 - Create a context.
  EGLContext eglContext;
  eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
  // Step 8 - Bind the context to the current thread
  eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
  GLuint fboId = 0;
  GLuint renderBufferWidth = 1920;
  GLuint renderBufferHeight = 1080;
  // Step 9 - create a framebuffer object
  glGenFramebuffers(1, &fboId);
  glBindFramebuffer(GL_FRAMEBUFFER, fboId);
  GLuint renderBuffer;
  glGenRenderbuffers(1, &renderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, renderBufferWidth, renderBufferHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
  GLuint depthRenderbuffer;
  glGenRenderbuffers(1, &depthRenderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, renderBufferWidth, renderBufferHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
  // Step 10 - check FBO status
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE)
    {
      printf("Problem with OpenGL framebuffer after specifying color render buffer: \n%x\n", status);
    }
  else
    {
      printf("FBO creation succedded\n");
    }
  int size = 4 * renderBufferHeight * renderBufferWidth;
  unsigned char *data2 = new unsigned char[size];
  // Step 11 - clear the screen in Red and read it back
  glClearColor(1.0,0.0,0.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  eglSwapBuffers( eglDisplay, eglSurface);
  glReadPixels(0,0,renderBufferWidth,renderBufferHeight,GL_RGBA, GL_UNSIGNED_BYTE, data2);

  // rgba -> bgra
  int w = renderBufferWidth, h = renderBufferHeight, pixel_byte = 4;
  unsigned char* pixels = data2;
  for (int i = 0; i < w*h; i++) {
    unsigned char *p = pixels+i*pixel_byte;
    std::swap(p[0], p[2]);
  }

  // mirror v
  int line_size = w*pixel_byte;
  auto swap_area = new char[w*h*pixel_byte];
  for (int i = 0; i < h/2; i++) {
    memcpy(swap_area, pixels+i*line_size, line_size);
    memcpy(pixels+i*line_size, pixels+(h-i-1)*line_size, line_size);
    memcpy(pixels+(h-i-1)*line_size, swap_area, line_size);
  }
  delete[] swap_area;

  // to png
  auto surface = cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, w, h, w * pixel_byte);
  cairo_surface_write_to_png(surface, "out.png");
  cairo_surface_destroy(surface);
}
