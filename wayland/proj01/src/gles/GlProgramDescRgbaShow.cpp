#include "GlProgramDescRgbaShow.hpp"
#include "GlProgramObject.hpp"

#include "utils/log/Log.hpp"

void
GlProgramDescRgbaShow::Process(GlProgramObject *program)
{
// Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program->Object(), "a_position");
    GLint texCoordLoc = glGetAttribLocation(program->Object(), "a_texCoord");
// Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program->Object(), "s_texture_rgba");

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

// Use the program object
    glUseProgram(program->Object());
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

    LogD << "GlProgramDescRgbaShow::Process done";
}

void
GlProgramDescRgbaShow::BindTexture(GLint textureId)
{
    texture = textureId;
}
