#include <utils/log/Log.hpp>
#include "WidgetGL.hpp"

FBO::FBO(int w, int h)
  : texWidth(w)
  , texHeight(h)
{
  mpShader = new Shader("src/gles/shaders/rgbashow.vert",
                        "src/gles/shaders/rgbashow.frag");
  mpShaderFBO = new Shader("src/gles/shaders/testfbo.vert",
                           "src/gles/shaders/testfbo.frag");

  GLint maxRenderbufferSize;
  glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
  if((maxRenderbufferSize <= texWidth)
     || (maxRenderbufferSize <= texHeight)) {
      // cannot use framebuffer objects as we need to create
      // a depth buffer as a renderbuffer object
      // return with appropriate error
      LogE << "maxRenderbufferSize <= w or h";
  }
}

bool FBO::checkFramebufferStatus()
{
  // check FBO status
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  switch(status)
  {
  case GL_FRAMEBUFFER_COMPLETE:
    LogD << "Framebuffer complete";
    return true;
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    LogI << "Framebuffer incomplete: Attachment is NOT complete";
    return false;
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    LogI << "Framebuffer incomplete: No image is attached to FBO";
    return false;
  case GL_FRAMEBUFFER_UNSUPPORTED:
    LogI << "Framebuffer incomplete:Unsupported by FBO implementation";
    return false;
  default:
    LogE << "Framebuffer incomplete: Unknown error";
    return false;
  }
}

void FBO::RenderToFBO()
{
  // render to texture using FBO
  // clear color and depth buffer
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
  GLint defaultFBO;
  GLint defaultRBO;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
  glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);

  glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
  if((maxRenderbufferSize <= texWidth) ||
     (maxRenderbufferSize <= texHeight))
  {
    LogE << "cannot use framebuffer objects as we need to create";
    return 0;
  }

  // frame buffer object
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  // render buffer object
  glGenRenderbuffers(1, &depthRenderbuffer);

  // bind renderbuffer and create a 16-bit depth buffer
  // width and height of renderbuffer = width and height of
  // the texture
  glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
                        texWidth, texHeight);

  // texture object name
  glGenTextures(1, &texture);
  // bind texture and load the texture mip-level 0
  // texels are RGB565
  // no texels need to be specified as we are going to draw into
  // the texture
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight,
               0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // combine all
  // specify texture as color attachment
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, texture, 0);
  // specify depth_renderbufer as depth attachment
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, depthRenderbuffer);

  if (checkFramebufferStatus()) {
    RenderToFBO();

    // bind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);

    // render to window system provided framebuffer
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    DrawScreenQuad();
  }

  // cleanup
  glDeleteRenderbuffers(1, &depthRenderbuffer);
  glDeleteFramebuffers(1, &framebuffer);
  glDeleteTextures(1, &texture);

  return 0;
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
