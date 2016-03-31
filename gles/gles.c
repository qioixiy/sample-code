
#include "gles.h"

#include <stdio.h>
#include <GLES2/gl2.h>

void print_gles_env(void)
{
    printf("\ngles env\n");

    GLint maxVertexAttribs, maxVertexUniforms, maxVaryings;
    GLint maxVertexTextureUnits, maxCombinedTextureUnits;

#define print_get(p1, p2) \
    do {                                        \
        glGetIntegerv(p1, p2);                  \
        printf(#p1 ":%d\n", *p2);               \
    }while(0)

    print_get(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    print_get(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniforms);
    print_get(GL_MAX_VARYING_VECTORS, &maxVaryings);
    print_get(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
              &maxVertexTextureUnits);
    print_get(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
              &maxCombinedTextureUnits);
}
