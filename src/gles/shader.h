
#ifndef _SHADER_H_
#define _SHADER_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C"
{
#endif

GLuint make_program_object(const char *vert, const char *frag);

GLuint load_program(const char*, const char*);
void dump_gl_program(GLuint);
GLuint get_program_object_default();
GLuint get_program_object_drawrect();
GLuint get_program_object_showyuyv();
GLuint get_program_object_shownv12();
GLuint get_program_object_showrgba();
GLuint get_program_object_mvptest();

#ifdef __cplusplus
}
#endif

#endif
