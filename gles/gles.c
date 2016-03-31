
#include "gles.h"

#include <stdio.h>
#include <GLES2/gl2.h>

void print_gles_env(void)
{
    printf("\ngles env\n");
    GLint maxVertexAttribs;
// n will be >= 8
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    printf("GL_MAX_VERTEX_ATTRIBS=%d\n", maxVertexAttribs);
}
