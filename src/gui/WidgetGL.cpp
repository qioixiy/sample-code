#include "WidgetGL.hpp"
#include <iostream>
using namespace std;

FBO::FBO(int w, int h)
    : texWidth(w)
    , texHeight(h)
{
    mpShader = new Shader("res/glsl_shaders/rgbashow.vert",
                          "res/glsl_shaders/rgbashow.frag");
    mpShaderFBO = new Shader("res/glsl_shaders/testfbo.vert",
                           "res/glsl_shaders/testfbo.frag");
}
bool FBO::checkFramebufferStatus()
{
    // check FBO status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE:
        //printf("Framebuffer complete.\n");
        return true;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        printf("Framebuffer incomplete: Attachment is NOT complete.\n");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        printf("Framebuffer incomplete: No image is attached to FBO.\n");
        return false;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        printf("Framebuffer incomplete:Unsupported by FBO implementation.\n");
        return false;
    default:
        printf("Framebuffer incomplete: Unknown error.\n");
        return false;
    }
}

void FBO::RenderToFBO()
{
    GLuint program_object = mpShaderFBO->GetObject();

    GLint colorLoc = glGetUniformLocation(program_object, "u_colorLoc");
    GLfloat rgba[4] = {1.50f, 1.0f, .50f, 1.0f};
    glUniform4fv(colorLoc, 1, rgba);
    GLfloat vVertices[] = {-1.0f, 1.0f, 0.0f,
                           1.0f, 1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                           -1.0f, 1.0f, 0.0f};
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FBO::DrawScreenQuad()
{
    GLuint program_object = mpShader->GetObject();
    // Use the program object
    glUseProgram(program_object);
// Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
// Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program_object, "s_texture_rgba");

    GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0
                            -1.0f, -1.0f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            1.0f, -1.0f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            1.0f,  1.0f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

// Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
// Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
// Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
// Set the base sampler to texture unit to 0
    glUniform1i(texture_rgba_loc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

int FBO::UseFBO ()
{
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
    if((maxRenderbufferSize <= texWidth) ||
       (maxRenderbufferSize <= texHeight))
    {
        printf("cannot use framebuffer objects as we need to create\n");
        return 0;
    }
    glGenFramebuffers(1, &framebuffer);
    glGenRenderbuffers(1, &depthRenderbuffer);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight,
                 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
                          texWidth, texHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthRenderbuffer);

    if (checkFramebufferStatus()) {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderToFBO();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        DrawScreenQuad();
    }
    glDeleteRenderbuffers(1, &depthRenderbuffer);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &texture);
}

WidgetGL::WidgetGL(int x, int y, int w, int h)
    :Widget(x, y, w, h)
    , mFBO(w, h)
{
    ;
}

int WidgetGL::draw()
{
    mFBO.UseFBO();
    return 0;
}
