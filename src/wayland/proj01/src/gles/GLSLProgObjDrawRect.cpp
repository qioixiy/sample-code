#include "GLSLProgObjDrawRect.hpp"

GLSLProgObjDrawRect::GLSLProgObjDrawRect(int r, int g, int b)
  : r(r), g(g), b(b)
{
  ;
}

void GLSLProgObjDrawRect::SetColor(int r, int g, int b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

int GLSLProgObjDrawRect::Runner()
{
  GLuint program_object = objs["drawrect"]->GetObject();
  // Use the program object
  glUseProgram(program_object);

  GLint colorLoc = glGetUniformLocation(program_object, "colorLoc");
  GLfloat rgba[4] = {r/256.0f, g/256.0f, b/256.0f, 1.0f};
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

  return 0;
}
