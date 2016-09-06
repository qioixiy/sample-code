
#ifndef _WIDGET_GL_HPP_
#define _WIDGET_GL_HPP_

#include "Widget.hpp"

class FBO {
public:
    FBO(int=64, int=64);

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

class WidgetGL : public Widget {
public:
    WidgetGL(int x, int y, int w, int h);

    virtual int draw();

private:
    FBO mFBO;
};

#endif
