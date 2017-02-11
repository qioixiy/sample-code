#ifndef _GLES_FBO_HPP_
#define _GLES_FBO_HPP_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "Shader.hpp"

class FBO
{
public:
    FBO(int = 64, int = 64);

    void RenderToFBO();
    void DrawScreenQuad();
    bool checkFramebufferStatus();
    bool FBOInit();
    int UseFBO ();

private:
    GLuint texture;
    GLint texWidth, texHeight;
    GLuint framebuffer;
    GLuint depthRenderbuffer;
    GLint maxRenderbufferSize;

    Shader *mpShader;
    Shader *mpShaderFBO;
};

#endif
