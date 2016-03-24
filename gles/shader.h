
#ifndef _SHADER_H_
#define _SHADER_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

GLuint load_program(const char *vertShaderSrc, const char *fragShaderSrc);
GLuint get_program_object_default();
GLuint get_program_object_drawrect();
GLuint get_program_object_showyuyv();
GLuint get_program_object_showrgba();

#endif
