
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C"
{
#endif

    GLuint gen_texture_from_data(unsigned char* , int, int, GLenum format);
    GLuint gen_texture_from_file(const char *file, int w, int h, GLenum format);

#ifdef __cplusplus
}
#endif

#endif
