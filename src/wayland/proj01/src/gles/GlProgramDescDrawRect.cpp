#include "GlProgramDescDrawRect.hpp"
#include "GlProgramObject.hpp"

#include "utils/log/Log.hpp"

void
GlProgramDescDrawRect::Process(GlProgramObject *program)
{
  glUseProgram(program->Object());

  GLint colorLoc = glGetUniformLocation(program->Object(), "colorLoc");
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

  LogD << "GlProgramDescDrawRect::Process done";
}

void
GlProgramDescDrawRect::SetColor(int _r, int _g, int _b)
{
  r = _r;
  g = _g;
  b = _b;
}
