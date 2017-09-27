#include "GlProgramDescDefault.hpp"
#include "GlProgramObject.hpp"

void
GlProgramDescDefault::Process(GlProgramObject *program)
{
    // Use the program object
    glUseProgram(program->Object());

    GLint colorLoc = glGetUniformLocation(program->Object(), "colorLoc");
    GLfloat rgba[4] = {.0f, .0f, 1.0f, 1.0f};
    glUniform4fv(colorLoc, 1, rgba);
    GLfloat vVertices[] = { -1.0f, 1.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f,
                            -1.0f, -1.0f, 0.0f,
                            -1.0f, 1.0f, 0.0f
                          };

// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    LogD << "GlProgramDescDefault::Process done";
}
