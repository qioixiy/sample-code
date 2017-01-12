#include <GLES2/gl2.h>
#include "GlEnv.hpp"
#include "utils/log/Log.hpp"

void GlEnv::PrintEnv(void)
{
  GLint maxVertexAttribs, maxVertexUniforms, maxVaryings;
  GLint maxVertexTextureUnits, maxCombinedTextureUnits;
  GLint maxRenderbufferSize;

#define GetAndPrint(p1, p2)                     \
  do {                                          \
    glGetIntegerv(p1, p2);                      \
    LogI << #p1 << *p2;                         \
  }while(0)

  GetAndPrint(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
  GetAndPrint(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniforms);
  GetAndPrint(GL_MAX_VARYING_VECTORS, &maxVaryings);
  GetAndPrint(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
              &maxVertexTextureUnits);
  GetAndPrint(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
              &maxCombinedTextureUnits);
  GetAndPrint(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
}
